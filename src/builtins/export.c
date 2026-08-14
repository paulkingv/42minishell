/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/08/14 16:15:44 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_array(t_env **array)
{
	t_env	*tmp;
	int i;

	i = 0;
	while (array[i] && array[i + 1])
	{
		if (ft_strcmp(array[i]->key,array[i + 1]->key) > 0)
		{
			tmp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

// adjust this to print in alpha order. add helper
static void	ft_print_export(t_shell *shell)
{
	t_env	**tmp;
	int		i;

	//tmp = env_to_array(shell->env);
	tmp = export_array(shell->env); //needs building
	if (!tmp)
		return ;
	sort_array(tmp);
	i = 0;
	while (tmp[i])
	{
		ft_printf("declare -x ");
		if (!tmp[i]->value)
			ft_printf("%s\n", tmp[i]->key);
		else if (!ft_strcmp(tmp[i]->value, "\"\""))
			ft_printf("%s=\n", tmp[i]->key);
		else
			ft_printf("%s=\"%s\"\n", tmp[i]->key, tmp[i]->value);
		i++;
	}
	free(tmp);
}

static char	**ft_export_util(t_cmd *cmd, int i)
{
	char	**strings;
	char	*equal;

	strings = ft_calloc(3, sizeof(char *));
	equal = ft_strchr(cmd->args[i], '=');
	if (!equal)
	{
		strings[0] = ft_strdup(cmd->args[i]);
		return (strings);
	}
	strings[0] = ft_substr(cmd->args[i], 0, equal - cmd->args[i]);
	strings[1] = ft_strdup(equal + 1);
	return (strings);
}

// export with no options
// add helper to reject not alpha chars in var names.
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
