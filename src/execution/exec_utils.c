/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_close_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 02:12:32 by pking             #+#    #+#             */
/*   Updated: 2026/08/28 05:18:14 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// closes pipes
void	exec_close_pipe(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

// Helper for EXECUTION.C just to check if prev_fd is registered
// line 21: if prev_fd is registered
// line 23: protect closing standard input
// line 25: HOOK Up the content as the STDIN then unmaps the value of prev_fd
void	is_prevfd_registered(int prev_fd)
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

