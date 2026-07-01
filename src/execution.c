/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:09:24 by pking             #+#    #+#             */
/*   Updated: 2026/07/01 14:10:55 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// DO ALL THE STRUCT FUNCTIONS IN THIS NEED TO BE POINTERS? CUREENTLY THEY ARE NOT.

// First two functions are error handlers

static int	safe_pipe(int pipe_fd[2])
{
	pipe(pipe_fd);
	if (pipe_fd == -1)
	{
		perror("Pipe Error");
		exit(1);
	}
	return (0);
}

static pid_t safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit (1);
	}
	return (pid);
}
// returns the number of the write end of pipe to the prev_fd for use in next iter
// Also handles cleaning up (closing)
static int parent_cleanup_exe_cmd(int prev_fd, int pipe_fd[2], t_cmd cmd)
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
static void child_exe_cmd(int prev_fd, int pipe_fd[2], t_cmd cmd)
{
	if (prev_fd != -1) // if prev_fd is registered
	{
	// HOOK Up the content as the STDIN
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd); // unmaps the value of prev_fd (val points to no existing FD)
	}
	if (cmd->next) // have to set up where we write to. Pipe FD overwrite STDOUT
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
		execvp(cmd->args[0], cmd->args); // this executes all the flags for the arg
		perror("execvp error in child");
		exit(1);
}
// The meat function. This is called in order to execute the line that has been parsed.
void exe_cmdline(t_cmd cmdline)
{
	int		prev_fd;
	int		pipe_fd[2];
	pid_t pid;

	prev_fd = -1;		// Prev FD exists out of Bounds (aka not registered)
    while (cmdline)
	{
		if (cmdline->next)
			safe_pipe(pipe_fd); // error handling pipe improved function
		pid = safe_fork(); // error handling fork improved function
		if (pid == 0)
			child_exe_cmd(prev_fd, pipe_fd, cmdline);
		prev_fd = parent_cleanup_exe_cmd(prev_fd, pipe_fd, cmdline);
		cmdline = cmdline->next;
	}
	waitpid(pid, NULL, 0);
}
