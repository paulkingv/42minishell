/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:53:57 by pking             #+#    #+#             */
/*   Updated: 2026/07/23 12:13:48 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args)
		return (0);
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (1);
	else
		return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	t_shell	*tmp = NULL;
	t_cmd	*tmp_cmd = NULL;
	int status;

	tmp = shell;
	tmp_cmd = cmd;
	status = 0;
	if (!ft_strncmp(shell->cmdline->args[0], "echo", 5))
		status = ft_echo(tmp);
	else	if (!ft_strncmp(shell->cmdline->args[0], "cd", 3))
		status = ft_cd(tmp, tmp_cmd);
	else if (!ft_strncmp(shell->cmdline->args[0], "pwd", 4))
		status = ft_pwd(tmp);
	else if (!ft_strncmp(shell->cmdline->args[0], "export", 7))
		status = ft_export(tmp, tmp_cmd);
	else if (!ft_strncmp(shell->cmdline->args[0], "unset", 6))
		status = ft_unset(tmp, tmp_cmd);
	else if (!ft_strncmp(shell->cmdline->args[0], "env", 4))
		status = ft_env(tmp);
	else if (!ft_strncmp(shell->cmdline->args[0], "exit", 5))
		status = ft_exit(tmp);
	return (status);
}
