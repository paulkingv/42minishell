/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 23:45:27 by pking             #+#    #+#             */
/*   Updated: 2026/08/30 19:17:21 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_builtin(t_shell *shell, t_cmd *cmd)
{
	int	status;

// signal(SIGPIPE, SIG_IGN);
	status = exec_builtin(shell, cmd);
	free_shell(shell);
	exit (status);
}
