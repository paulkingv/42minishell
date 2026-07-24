/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/07/24 12:50:32 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo with option -n
int	ft_echo_n(t_shell *shell)
{
//not sur eon exit status, but this function works. However not for all -n cases
	t_cmd	*tmp;
	char	**arg;
	int		i;

	tmp = shell->cmdline;
	arg = tmp->args;
	i = 2;
	if (arg[i])
	{
		while (!(ft_strncmp((arg[i]), "-n", 3)))
			i++;
		while (arg[i])
		{
			ft_printf("%s", arg[i]);
			if (arg[i + 1])
				ft_printf(" ", arg[i]);
			i++;
		}
		shell->exit = 0;
		return (0);
	}
	shell->exit = 1;
	return (1);
}

// echo
int	ft_echo(t_shell *shell)
{
//NOT CONVINCED ABOUT THE EXIT STATUS
	t_cmd	*tmp;
	char	**arg;
	int		i;

	tmp = shell->cmdline;
	arg = tmp->args;
	i = 1;
	if (!arg[i])
	{
		shell->exit = 1;
		ft_printf("\n");
		return (1);
	}
	if (!(ft_strncmp((arg[1]), "-n", 2)))
	{
		shell->exit = ft_echo_n(shell);
		return (shell->exit);
	}
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			ft_printf(" ", arg[i]);
		i++;
	}
	ft_printf("\n", arg[i]);
	shell->exit = 0;
	return (0);
}

// cd with only a relative or absolute path
int	ft_cd(t_shell *shell, t_cmd *cmd)
{
// NEED TO WORK ON RELATIVE PATH VERSION
	char	*new_path;
	char	*old_path;

	old_path = get_env(shell->env, "PWD");
	if (old_path)
	{
		if (cmd->args[1])
			new_path = cmd->args[1];
		else
			new_path = get_env(shell->env, "HOME");
		if (!(chdir(new_path)))
		{
			set_env(&shell->env, "OLDPWD", old_path);
			set_env(&shell->env, "PWD", new_path);
		}
		else
			ft_printf("No such file or directory.\n");
		shell->exit = 0;
		return (0);
	}
	shell->exit = 1;
	return (1);
}

// pwd with no options
int	ft_pwd(t_shell	*shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		shell->exit = 0;
		return (0);
	}
	else
	{
		perror("pwd");
		shell->exit = 1;
		return (1);
	}
}
