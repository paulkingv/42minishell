/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:25:55 by jfox              #+#    #+#             */
/*   Updated: 2026/07/31 13:29:50 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle $?
static void	ft_echo_exit(t_shell *shell, char **args, int i)
{
	while (args[i])
	{
		if (args[i + 1])
		{
			if (!ft_strncmp(args[i + 1], "+", 2)
				&& !ft_strncmp(args[i + 2], "$?", 3))
				ft_printf("%d", shell->exit + shell->exit);
		}
		else
			ft_printf("%d", shell->exit);
		return ;
	}
}

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
		if (!ft_strncmp(args[i], "$?", 3))
		{
			ft_echo_exit(shell, args, i);
			break;
		}
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
