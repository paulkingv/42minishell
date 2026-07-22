/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:09:24 by pking             #+#    #+#             */
/*   Updated: 2026/07/22 03:56:37 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper to free our array on close
static void valid_cmd_null_cleanup(t_cmd *cmdline, char **envp)
{
	write (2, "minishell: ", 11);
	if(cmdline && cmdline->args[0])
		write(2, cmdline->args[0], ft_strlen(cmdline->args[0]));
	write(2, ": command not found\n", 20);
	free_array(envp);
	exit(127);
}

// returns the number of the write end of pipe to the prev_fd for use in next iter
// Also handles cleaning up (closing)
// Added tmp struct to not touch shell.
static int parent_cleanup_exe_cmd(int prev_fd, int pipe_fd[2], t_cmd *tmp_cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (tmp_cmd->next)
	{
		close(pipe_fd[1]);
		return(pipe_fd[0]);
	}
	return (-1);
}
// Actual child executing the cmd part
static void child_exe_cmd(int prev_fd, int pipe_fd[2], t_shell *shell, t_cmd *tmp_cmd)
{
	char	*valid_cmd;
	char	**envp;

	if (prev_fd != -1) // if prev_fd is registered
	{
		safe_dup2(prev_fd, STDIN_FILENO);// HOOK Up the content as the STDIN
		close(prev_fd); // unmaps the value of prev_fd (val points to no existing FD)
	}
	if (tmp_cmd->next) // have to set up where we write to. Pipe FD overwrite STDOUT
		safe_dup2(pipe_fd[1], STDOUT_FILENO);
	if (tmp_cmd->next)
		exec_close_pipe(pipe_fd);
	if (tmp_cmd->redirections)
		handle_redirects(tmp_cmd->redirections);
	if (!tmp_cmd->args || !tmp_cmd->args[0])
		exit(0);
	if (is_builtin(tmp_cmd))
		exit(exec_builtin(tmp_cmd));
	envp = env_to_array(shell->env);
	valid_cmd = exec_get_valid_path(shell, tmp_cmd->args[0]);
	if (valid_cmd == NULL)
		valid_cmd_null_cleanup(tmp_cmd, envp);
	execve(valid_cmd, tmp_cmd->args, envp);
	perror("execve error in child");
	free_array(envp);
	free(valid_cmd);
	exit(1);
}
// The meat function. This is called in order to execute the line that has been parsed.
void exe_cmdline(t_shell *shell)
{
	t_cmd	*tmp_cmd = NULL;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t 	pid;

	tmp_cmd = shell->cmdline;
	prev_fd = -1;		// Prev FD exists out of Bounds (aka not registered)
	while (tmp_cmd)
	{
		if (tmp_cmd && !tmp_cmd->next && is_builtin(tmp_cmd))
		{
			//shell->exit = 
			exec_builtin(shell, tmp_cmd);
			return ; // special case: 1 built in exec
		}
		exec_init_pipefd(pipe_fd);
		if (tmp_cmd->next)
				safe_pipe(pipe_fd); // error handling pipe improved function
		pid = safe_fork(); // error handling fork improved function
		if (pid == 0)
			child_exe_cmd(prev_fd, pipe_fd, shell, tmp_cmd);
		prev_fd = parent_cleanup_exe_cmd(prev_fd, pipe_fd, tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
	while (waitpid(-1, &shell->exit, 0) > 0) // Special waiting line (Need 2 research)
		safe_exit(&shell->exit, shell);
}
