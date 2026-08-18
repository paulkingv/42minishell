/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/08/17 14:36:55 by jfox             ###   ########.fr       */
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
		else
			ft_printf("No such file or directory.\n");
	}
	return (1);
}

// pwd with no options
int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
