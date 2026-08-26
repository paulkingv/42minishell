/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/08/26 11:49:09 by jfox             ###   ########.fr       */
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
	return ;
}

// break the valid command argument into a string array holding key and value
static char	**ft_export_util(t_cmd *cmd, int i)
{
	char	**strings;
	char	*equal;
	int		key_len;

	strings = ft_calloc(3, sizeof(char *));
	if (!strings)
		return (NULL);
	equal = ft_strchr(cmd->args[i], '=');
	if (!equal)
	{
		strings[0] = ft_strdup(cmd->args[i]);
		return (strings);
	}
	key_len = equal - cmd->args[i];
	if (key_len > 0 && cmd->args[i][key_len - 1] == '+')
		key_len = key_len - 1;
	strings[0] = ft_substr(cmd->args[i], 0, key_len);
	strings[1] = ft_strdup(equal + 1);
	return (strings);
}

// check if the argument after export has a += and needs to append
static int	append(char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal || equal == arg)
		return (0);
	if (*(equal - 1) == '+')
		return (1);
	return (0);
}

// if we need to append, call this function, find the key in the environment
// if not findable, add the variable without the +=
// if found but empty, set the value of key
// otherwise append the value after += onto the existing value.
static void	append_env(t_shell *shell, char *key, char *value)
{
	t_env	*env;
	char	*joined;

	env = find_env(shell->env, key);
	if (!env)
	{
		set_env(&shell->env, key, value);
		return ;
	}
	if (!env->value)
	{
		set_env(&shell->env, key, value);
		return ;
	}
	joined = ft_strjoin(env->value, value);
	if (!joined)
		return ;
	set_env(&shell->env, key, joined);
	free(joined);
	return ;
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
			print_export_error(tcmd->args[i]);
			shell->exit = 1;
			i++;
			continue ;
		}
		strings = ft_export_util(tcmd, i);
		if (append(tcmd->args[i]))
			append_env(shell, strings[0], strings[1]);
		else
			set_env(&shell->env, strings[0], strings[1]);
		free_array(strings);
		i++;
	}
	return (shell->exit);
}
