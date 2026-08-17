/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/08/17 11:16:01 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// adjust this to print in alpha order. add helper
static void	ft_print_export(t_shell *shell)
{
	t_env	**tmp;
	int		i;

	tmp = export_array(shell->env);
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

// break the valid command argument into a string array holding key and value
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
		if (!valid_export(tcmd->args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(tcmd->args[i], 2);
			ft_putstr_fd("not a valid identifier\n", 2);
			shell->exit = 1;
			i++;
			continue;
		}
		strings = ft_export_util(tcmd, i);
		set_env(&shell->env, strings[0], strings[1]);
		free_array(strings);
		i++;
	}
	return (shell->exit);
}
