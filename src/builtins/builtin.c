/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/07/28 17:07:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -n check for echo
static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// echo with a check for option -n
int	ft_echo(t_shell *shell)
{
	char	**args;
	int		i;
	int		newline;

	args = shell->cmdline->args;
	i = 1;
	newline = 1;
	while (args[i] && is_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
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
		return (0);
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
