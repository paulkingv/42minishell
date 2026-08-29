/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 13:32:30 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 13:54:34 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the argument after export has a += and needs to append
int	append(char *arg)
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
void	append_env(t_shell *shell, char *key, char *value)
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
