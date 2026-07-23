/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:53:57 by pking             #+#    #+#             */
/*   Updated: 2026/07/23 10:40:31 by jfox             ###   ########.fr       */
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

//NOT FINISHED, NEEDS MATT TO DO THE BUILTINS
void	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	t_shell	*tmp = NULL;
	t_cmd	*tmp_cmd = NULL;

	tmp = shell;
	tmp_cmd = cmd;
	if (!strcmp(shell->cmdline->args[0], "echo"))
		ft_echo(tmp);
	else	if (!strcmp(shell->cmdline->args[0], "cd"))
		ft_cd(tmp, tmp_cmd);
	else if (!strcmp(shell->cmdline->args[0], "pwd"))
		ft_pwd();
	else if (!strcmp(shell->cmdline->args[0], "export"))
		ft_export(tmp, tmp_cmd);
	else if (!strcmp(shell->cmdline->args[0], "unset"))
		ft_unset(tmp, tmp_cmd);
	else if (!strcmp(shell->cmdline->args[0], "env"))
		ft_env(tmp);
	else if (!strcmp(shell->cmdline->args[0], "exit"))
		ft_exit(tmp);
	return ;
}
