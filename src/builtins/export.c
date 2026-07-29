/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/07/29 17:00:54 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_export(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	if (tmp)
	{
		while (tmp)
		{
			if (!tmp->value)
				ft_printf("%s=''\n", tmp->key);
			else
				ft_printf("%s=\'%s\'\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}

static char	**ft_export_util(t_cmd *cmd, int i)
{
	char	**strings;

	if (!ft_strchr(cmd->args[i], '='))
	{
		strings = ft_split(cmd->args[i], '=');
		return (strings);
	}
	strings = ft_split(cmd->args[i], '=');
	if (strings && !strings[1])
		strings[1] = "";
	return (strings);
}

// export with no options
int	ft_export(t_shell *shell, t_cmd *cmd, t_env *tmp, t_cmd *tmp_cmd)
{
	char	**strings;
	int		i;

	tmp = shell->env;
	tmp_cmd = cmd;
	i = 1;
	if (!tmp_cmd->args[i])
		ft_print_export(shell);
	while (tmp_cmd->args[i])
	{
		if (ft_isdigit(tmp_cmd->args[i][0]))
		{
			if (tmp_cmd->args[i + 1] == NULL)
				break ;
			i++;
		}
		strings = ft_export_util(tmp_cmd, i);
		set_env(&shell->env, strings[0], strings[1]);
		i++;
	}
	return (0);
}
