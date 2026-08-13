/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/08/13 17:22:24 by jfox             ###   ########.fr       */
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
			ft_printf("declare - x ");
			if (!tmp->value)
				ft_printf("%s\n", tmp->key);
			else if (!ft_strcmp(tmp->value, "\"\""))
				ft_printf("%s=\n", tmp->key);
			else
				ft_printf("%s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}



static char	**ft_export_util(t_cmd *cmd, int i)
{
	char	**strings;
	char	*equal;

	strings = ft_calloc(3, sizeof(char *));
	equal = ft_strchr(cmd->args[i], '=');
	if (!ft_strchr(cmd->args[i], '='))
	{
		strings[0] = ft_substr(cmd->args[i], 0, equal - cmd->args[i]);
		return (strings);
	}
	strings[0] = ft_substr(cmd->args[i], 0, equal - cmd->args[i]);
	strings[1] = ft_strdup(equal + 1);
	return (strings);
}

// export with no options
int	ft_export(t_shell *shell, t_cmd *cmd, t_cmd *tcmd)
{
	char	**strings;
	int		i;

	tcmd = cmd;
	i = 1;
	if (!tcmd->args[i])
		ft_print_export(shell);
	while (tcmd->args[i])
	{
		if (ft_isdigit(tcmd->args[i][0]) || !ft_strncmp(tcmd->args[i], "=", 1))
		{
			if (tcmd->args[i + 1] == NULL)
			{
				shell->exit = 1;
				break ;
			}
			i++;
		}
		strings = ft_export_util(tcmd, i);
		set_env(&shell->env, strings[0], strings[1]);
		free_array(strings);
		i++;
	}
	return (shell->exit);
}
