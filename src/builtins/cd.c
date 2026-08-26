/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/08/25 21:30:02 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper to set OLDPWD and PWD if we have no env on start up
static int	no_chdir(t_shell *shell, char *old_path, char *new_path)
{
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (1);
	set_env(&shell->env, "OLDPWD", old_path);
	set_env(&shell->env, "PWD", new_path);
	free(new_path);
	return (1);
}

// helper to print we have not found the file or dir at the path
static void	print_newpath(char *new_path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(new_path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

// helper function to action all of the cd work, returns an int to ft_cd
// ft_cd then passes the exit back to exec_builtins.
static int	act_cd(t_shell *shell, t_cmd *cmd, char *new_path, char *old_path)
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
		if (no_chdir(shell, old_path, new_path))
			return (0);
	}
	else if(new_path[0])
	{
		print_newpath(new_path);
		return (1);
	}
	return (0);
}

// cd with only a relative or absolute path
int	ft_cd(t_shell *shell, t_cmd *cmd, char *new_path, char *old_path)
{
	int	ret;

	ret = 0;
	old_path = get_env(shell->env, "PWD");
	if (!old_path)
		return (1);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("cd: too many arguments", 2);
		shell->exit = 1;
		return (1);
	}
	if (cmd->args[1] && !ft_strcmp(cmd->args[1], "--"))
		return (ret);
	ret = act_cd(shell, cmd, new_path, old_path);
	return (ret);
}
