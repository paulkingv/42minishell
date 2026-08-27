/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_prevfd_reg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:03:44 by pking             #+#    #+#             */
/*   Updated: 2026/08/27 22:05:03 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"


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
