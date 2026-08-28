/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:09:24 by pking             #+#    #+#             */
/*   Updated: 2026/08/28 01:28:49 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper just to check if prev_fd is registered
// line 21: if prev_fd is registered
// line 23: protect closing standard input
// line 25: HOOK Up the content as the STDIN then unmaps the value of prev_fd
static void	is_prevfd_registered(int prev_fd)
{
	if (prev_fd != -1)
	{
		if (prev_fd != STDIN_FILENO)
		{
			safe_dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
	}
}

// Helper to free our array on close
static void	invalid_cmd_cleanup(t_shell *shell, t_cmd *cmdline, char **envp,
	int exit_code)
{
	char *msg;

	msg = "command not found\n";
	if (exit_code == 126)
	{
		msg = "Permission denied\n";
		if (ft_strchr(cmdline->args[0], '/')
			&& is_directory(cmdline->args[0]))
		msg = "Is a directory";
	}
	write(2, "minishell: ", 11);
	if (cmdline && cmdline->args && cmdline->args[0])
		write(2, cmdline->args[0], ft_strlen(cmdline->args[0]));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	free_array(envp);
	free_shell(shell);
	exit(exit_code);
}

// returns the number of the write end of pipe to the prev_fd for use in next
// iter. Also handles cleaning up (closing)
// Added tmp struct to not touch shell.
static int	parent_cleanup_exe_cmd(int prev_fd, int pipe_fd[2], t_cmd *tmp_cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (tmp_cmd->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

// Actual child executing the cmd part
// line 66: have to set up where we write to. Pipe FD ow STDOUT

// Refactor later
static void	child_exe_cmd(int prev_fd, int pipe_fd[2],
	t_shell *shell, t_cmd *tmp_cmd)
{
	char	*valid_cmd;
	char	**envp;
	int		exit_code;

	default_signals();
	if (tmp_cmd->redirections // try read_heredocs & set up fds
		&& read_heredocs(tmp_cmd->redirections, shell) == -1)
		{
			if (g_signal_status == SIGINT)
				exit(130);
			exit(1);
		}
	is_prevfd_registered(prev_fd);
	if (tmp_cmd->next)
		safe_dup2(pipe_fd[1], STDOUT_FILENO);
	if (tmp_cmd->next)
		exec_close_pipe(pipe_fd);
	if (tmp_cmd->redirections)
		handle_redirects(tmp_cmd->redirections, shell->env, shell);
	if (!tmp_cmd->args || !tmp_cmd->args[0])
		exit(free_shell(shell));
	if (is_builtin(tmp_cmd))
		exec_child_builtin(shell, tmp_cmd);
	envp = env_to_array(shell->env);
	valid_cmd = exec_get_valid_path(shell, tmp_cmd->args[0], &exit_code);
	if (valid_cmd == NULL)
		invalid_cmd_cleanup(shell, tmp_cmd, envp, exit_code);
	execve(valid_cmd, tmp_cmd->args, envp);
	perror(tmp_cmd->args[0]);
	free(valid_cmd);
	free_array(envp);
	free_shell(shell);
	exit(126);
}

// The meat function. This is called to execute the line that has been parsed.
// line 102; Prev FD exists out of Bounds (aka not registered)
// line 105: shell->exit set inside the builtin cmd
// line 106: special case: 1 built in exec
// line 112: error handling pipe improved function
// line 13: error handling fork improved function
void	exe_cmdline(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	pid;

	tmp_cmd = shell->cmdline;
	prev_fd = -1;
	if (tmp_cmd && !tmp_cmd->next && is_builtin(tmp_cmd)
		&& !tmp_cmd->redirections)
	{
		exec_builtin(shell, tmp_cmd);
		return ;
	}
	parent_wait_signals();
	while (tmp_cmd)
	{
		if (is_builtin(tmp_cmd) && !tmp_cmd->redirections
			&& tmp_cmd->separator == SEMICOLON)
		{
			exec_builtin(shell, tmp_cmd);
			tmp_cmd = tmp_cmd->next;
			continue;
		}
		exec_init_pipefd(pipe_fd);
		if (tmp_cmd->next)
			safe_pipe(pipe_fd);
		pid = safe_fork();
		if (pid == 0)
			child_exe_cmd(prev_fd, pipe_fd, shell, tmp_cmd);
		prev_fd = parent_cleanup_exe_cmd(prev_fd, pipe_fd, tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
	wait_for_children(pid, shell);
	init_signals(0, NULL);
}
