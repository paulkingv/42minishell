/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 11:08:02 by jfox              #+#    #+#             */
/*   Updated: 2026/07/31 17:18:51 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit with no options
int	ft_exit(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;

	tmp = shell->cmdline;
	i = 0;
	if (tmp->args[1])
	{
		i = ft_atoi(tmp->args[1]);
		shell->status = 1;
		ft_printf("exit\n");
		return (i);
	}
	shell->status = 1;
	ft_printf("exit\n");
	return (0);
}

// unset with no options
int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->args[i])
	{
		unset_env(&shell->env, cmd->args[i]);
		i++;
	}
	return (0);
}

// env with no options or arguments
int	ft_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			if (!ft_strncmp(tmp->value, "\'\'", 3))
				ft_printf("%s=\n", tmp->key);
			else
				ft_printf("%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
