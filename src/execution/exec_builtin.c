/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:53:57 by pking             #+#    #+#             */
/*   Updated: 2026/07/13 16:04:17 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args[0])
		return (0);
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

// NOT FINISHED, NEEDS MATT TO DO THE BUILTINS
int exec_builtin(t_cmd *cmd, t_env *env)
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
	else
		return (-1);
	return (status);
}
