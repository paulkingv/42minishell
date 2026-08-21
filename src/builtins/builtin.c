/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/08/21 16:59:43 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd with only a relative or absolute path
int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*new_path;
	char	*old_path;

	old_path = get_env(shell->env, "PWD");
	if (old_path)
	{
		if (cmd->args[1] && cmd->args[2])
		{
			ft_putstr_fd("cd: too many arguments", 2);
			shell->exit = 1;
			return (1);
		}
		if (cmd->args[1])
			new_path = cmd->args[1];
		else
		{
			if (!find_env(shell->env, "HOME"))
			{
				ft_putstr_fd("cd: HOME not set\n", 2);
				return (1);
			}
			new_path = get_env(shell->env, "HOME");
			if (!new_path || !new_path[0])
				return (0);
		}
		if (!(chdir(new_path)))
		{
			set_env(&shell->env, "OLDPWD", old_path);
			set_env(&shell->env, "PWD", new_path);
			return (0);
		}
		else if(new_path[0])
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(new_path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("No such file or directory\n", 2);
		}
		else
			return (0);
	}
	return (1);
}

// pwd with no options
int	ft_pwd(t_shell *shell)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	pwd = get_env(shell->env, "PWD");
	if (pwd)
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	return (1);
}
