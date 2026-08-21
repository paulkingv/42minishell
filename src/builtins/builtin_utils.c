/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 11:08:02 by jfox              #+#    #+#             */
/*   Updated: 2026/08/21 17:18:19 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (!ft_strncmp(tmp->value, "\"\"", 3))
				ft_printf("%s=\n", tmp->key);
			else
				ft_printf("%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
