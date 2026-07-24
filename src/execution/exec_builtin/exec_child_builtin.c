/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 23:45:27 by pking             #+#    #+#             */
/*   Updated: 2026/07/24 11:29:07 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_builtin(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = exec_builtin(shell, cmd);
	free_shell(shell);
	exit (status);
}
