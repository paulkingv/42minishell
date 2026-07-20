/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:53:57 by pking             #+#    #+#             */
/*   Updated: 2026/07/20 15:56:04 by jfox             ###   ########.fr       */
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
	else if (!strcmp(cmd->args[0], "env"))
		return (1);
	else if (!strcmp(cmd->args[0], "exit"))
		return (1);
	else
		return (0);
}

//NOT FINISHED, NEEDS MATT TO DO THE BUILTINS
void	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	t_shell	*tmp = NULL;
	t_cmd	*tmp_cmd = NULL;

	tmp = shell;
	tmp_cmd = cmd;
	// if (!strcmp(shell->cmdline->args[0], "echo"))
	// 	ft_echo(tmp);
	// else if (!strcmp(shell->cmdline->args[0], "cd"))
	// 	ft_cd(tmp);
	// else if (!strcmp(shell->cmdline->args[0], "pwd"))
	// 	ft_pwd(tmp);
	// else
	if (!strcmp(shell->cmdline->args[0], "export"))
		ft_export(tmp, tmp_cmd);
	else if (!strcmp(shell->cmdline->args[0], "unset"))
		ft_unset(tmp, tmp_cmd);
	else if (!strcmp(shell->cmdline->args[0], "env"))
		ft_env(tmp);
	// else if (!strcmp(shell->cmdline->args[0], "exit"))
	// 	ft_exit(tmp);
	return ;
}
