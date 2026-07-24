/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 11:08:02 by jfox              #+#    #+#             */
/*   Updated: 2026/07/24 11:12:36 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit with no options
int	ft_exit(t_shell *shell)
{
	shell->status = 1;
	shell->exit = 0;
	ft_printf("exit\n");
	return (0);
}

// env with no options or arguments
int	ft_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	if (tmp)
	{
		while (tmp)
		{
			ft_printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		shell->exit = 0;
		return (0);
	}
	shell->exit = 1;
	return (1);
}

// unset with no options
int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	if (cmd)
	{
		unset_env(&shell->env, cmd->args[1]);
		shell->exit = 0;
		return (0);
	}
	shell->exit = 1;
	return (1);
}

// export with no options
int	ft_export(t_shell *shell, t_cmd *cmd)
{
	t_env	*tmp;
	t_cmd	*tmp_cmd;
	char	**strings;

	tmp = shell->env;
	tmp_cmd = cmd;
	if (tmp_cmd)
	{
		strings = ft_split(tmp_cmd->args[1], '=');
		set_env(&tmp, strings[0], strings[1]);
		free_array(strings);
		shell->exit = 0;
		return (0);
	}
	shell->exit = 1;
	return (1);
}
