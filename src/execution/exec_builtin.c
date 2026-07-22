/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:53:57 by pking             #+#    #+#             */
/*   Updated: 2026/07/22 03:53:00 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args[0])
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

	tmp = shell;
	tmp_cmd = cmd;
	// if (!ft_strncmp(shell->cmdline->args[0], "echo", 5))
	// 	ft_echo(tmp);
	// else
	if (!ft_strncmp(shell->cmdline->args[0], "cd", 3))
		ft_cd(tmp, tmp_cmd);
	else if (!ft_strncmp(shell->cmdline->args[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(shell->cmdline->args[0], "export", 7))
		ft_export(tmp, tmp_cmd);
	else if (!ft_strncmp(shell->cmdline->args[0], "unset", 6))
		ft_unset(tmp, tmp_cmd);
	else if (!ft_strncmp(shell->cmdline->args[0], "env", 4))
		ft_env(tmp);
	else if (!ft_strncmp(shell->cmdline->args[0], "exit", 5))
		ft_exit(tmp);
	return (0);
}
