/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:09:24 by pking             #+#    #+#             */
/*   Updated: 2026/07/16 16:42:23 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the number of the write end of pipe to the prev_fd for use in next iter
// Also handles cleaning up (closing)
static int parent_cleanup_exe_cmd(int prev_fd, int pipe_fd[2], t_shell *shell)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (shell->cmdline->next)
	{
		close(pipe_fd[1]);
		return(pipe_fd[0]);
	}
	return (-1);
}
// Actual child executing the cmd part
static void child_exe_cmd(int prev_fd, int pipe_fd[2], t_shell *shell)
{
	char	**envp;

	if (prev_fd != -1) // if prev_fd is registered
	{
	// HOOK Up the content as the STDIN
		safe_dup2(prev_fd, STDIN_FILENO);
		close(prev_fd); // unmaps the value of prev_fd (val points to no existing FD)
	}
	if (shell->cmdline->next) // have to set up where we write to. Pipe FD overwrite STDOUT
		safe_dup2(pipe_fd[1], STDOUT_FILENO);

	exec_close_pipe(pipe_fd);
	if (shell->cmdline->redir)
		handle_redirects(shell->cmdline->redir);
	envp = env_to_array(shell->env);
	execve(shell->cmdline->args[0], shell->cmdline->args, envp);
	perror("execve error in child");
	exit(1);
}
// The meat function. This is called in order to execute the line that has been parsed.
void exe_cmdline(t_shell *shell)
{
	int		prev_fd;
	int		pipe_fd[2];
	int		exit;
	pid_t 	pid;
	
	prev_fd = -1;		// Prev FD exists out of Bounds (aka not registered)
    while (shell->cmdline)
	{
		if (is_builtin(shell->cmdline))
		{
			exit = exec_builtin(shell->cmdline, &shell->env); // idk how to do this w shell struct
			shell->cmdline = shell->cmdline->next;
			continue; // this keyword resets the while(cmd) loop from the top
		}
		if (shell->cmdline->next)
			safe_pipe(pipe_fd); // error handling pipe improved function
		pid = safe_fork(); // error handling fork improved function
		if (pid == 0)
			child_exe_cmd(prev_fd, pipe_fd, shell->cmdline, shell->env);
		prev_fd = parent_cleanup_exe_cmd(prev_fd, pipe_fd, shell->cmdline);
		shell->cmdline = shell->cmdline->next;
	}
	while (waitpid(-1, &exit, 0) > 0); // Special waiting line (Need 2 research)
		safe_exit(&exit, shell);
}
