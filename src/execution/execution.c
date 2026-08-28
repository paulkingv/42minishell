/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:09:24 by pking             #+#    #+#             */
/*   Updated: 2026/08/28 05:15:10 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper to free our array on close
void	invalid_cmd_cleanup(t_shell *shell, t_cmd *cmdline,
	char **envp, int exit_code)
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

static void execute_pipeline(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	pid;

	tmp_cmd = shell->cmdline;
	prev_fd =-1;
	while(tmp_cmd)
	{
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

// The entry point. This is called to execute the line that has been parsed. 
void	exe_cmdline(t_shell *shell)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = shell->cmdline;
	if (tmp_cmd && !tmp_cmd->next && is_builtin(tmp_cmd)
		&& !tmp_cmd->redirections)
	{
		exec_builtin(shell, tmp_cmd);
		return ;
	}
	parent_wait_signals();
	execute_pipeline(shell);
}
