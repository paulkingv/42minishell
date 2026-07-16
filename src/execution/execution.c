/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:09:24 by pking             #+#    #+#             */
/*   Updated: 2026/07/16 02:57:05 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the number of the write end of pipe to the prev_fd for use in next iter
// Also handles cleaning up (closing)
static int parent_cleanup_exe_cmd(int prev_fd, int pipe_fd[2], t_cmd *cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		return(pipe_fd[0]);
	}
	return (-1);
}
// Actual child executing the cmd part
static void child_exe_cmd(int prev_fd, int pipe_fd[2], t_cmd *cmd, t_env *env)
{
	char	**envp;

	if (prev_fd != -1) // if prev_fd is registered
	{
	// HOOK Up the content as the STDIN
		safe_dup2(prev_fd, STDIN_FILENO);
		close(prev_fd); // unmaps the value of prev_fd (val points to no existing FD)
	}
	if (cmd->next) // have to set up where we write to. Pipe FD overwrite STDOUT
		safe_dup2(pipe_fd[1], STDOUT_FILENO);
	exec_close_pipe(pipe_fd);
	if (cmd->redir)
		handle_redirects(cmd->redir);
	envp = env_to_array(env);
	execve(cmd->args[0], cmd->args, envp);
	perror("execve error in child");
	exit(1);
}
// The meat function. This is called in order to execute the line that has been parsed.
int exe_cmdline(t_cmd *cmd, t_env *env)
{
	int		prev_fd;
	int		pipe_fd[2];
	int		exit_code;
	pid_t pid;
	
	prev_fd = -1;		// Prev FD exists out of Bounds (aka not registered)
    while (cmd)
	{
		if (is_builtin(cmd))
		{
			exit_code = exec_builtin(cmd, &env);
			cmd = cmd->next;
			continue; // this keyword resets the while(cmd) loop from the top
		}
		if (cmd->next)
			safe_pipe(pipe_fd); // error handling pipe improved function
		pid = safe_fork(); // error handling fork improved function
		if (pid == 0)
			exit_code = child_exe_cmd(prev_fd, pipe_fd, cmd, env);
		prev_fd = parent_cleanup_exe_cmd(prev_fd, pipe_fd, cmd);
		cmd = cmd->next;
	}
	while (waitpid(-1, &exit_code, 0) > 0); // Special waiting line (Need 2 research)
	shell->exit_code = exit_code;
}
