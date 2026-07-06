/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:53:57 by pking             #+#    #+#             */
/*   Updated: 2026/07/06 17:22:24 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->args[0], "echo"))
		return (1);
	else if (!strcmp(cmd->args[0], "cd"))
		return (1);
	else if (!strcmp(cmd->args[0], "pwd"))
		return (1);
	else if (!strcmp(cmd->args[0], "export"))
		return (1);
	else if (!strcmp(cmd->args[0], "unset"))
		return (1);
	else if (!strcmp(cmd->args[0], "exit"))
		return (1);
	else
		return (0);
}

int exec_builtin(t_cmd *cmd)
{
	int status;
	if (!strcmp(cmd->args[0], "echo"))
		status = ft_echo()
	else if (!strcmp(cmd->args[0], "cd"))
		status = ft_cd()
	else if (!strcmp(cmd->args[0], "pwd"))
		status = ft_pwd()
	else if (!strcmp(cmd->args[0], "export"))
		status = ft_export()
	else if (!strcmp(cmd->args[0], "unset"))
		status = ft_unset()
	else if (!strcmp(cmd->args[0], "exit"))
		status = ft_exit()
	return (status);
}
