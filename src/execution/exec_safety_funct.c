/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_safety_funct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 02:16:14 by pking             #+#    #+#             */
/*   Updated: 2026/07/22 20:45:52 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int safe_dup2(int fd, int target_fd)
{
	int result;
	
	result = dup2(fd, target_fd);
	if (result == -1)
		{
			perror("error dup2 when redirecting");
			exit(1);
		}
	return (result);
}

pid_t safe_fork(void)
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


int	safe_pipe(int pipe_fd[2])
{
	int return_code;

	return_code = pipe(pipe_fd);
	if (return_code == -1)
	{
		perror("Pipe Error");
		exit(1);
	}
	return (0);
}

void wait_for_children(pid_t last_pid, t_shell *shell)
{
	pid_t	reaped_pid;
	int		status;

	reaped_pid = waitpid(-1, &status, 0);
	while (reaped_pid > 0)
	{
		if (reaped_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				shell->exit = 128 + WTERMSIG(status);
		}
		reaped_pid = waitpid(-1, &status, 0);
	}
}