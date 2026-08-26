/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:38:11 by jfox              #+#    #+#             */
/*   Updated: 2026/08/26 00:29:00 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// As with all structs, a handle to create the node for a chained list.
// Here we also pass information so we fill the struct while we initialize it.
t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else	
		new->value = NULL;
	new->next = NULL;
	return (new);
}

// A simply string compare helper to check if the current environment variable
// is the one we are looking for, it returns a pointer to the desired variable.
t_env	*find_env(t_env *s_env, char *key)
{
	t_env	*tmp;

	tmp = s_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// Similar to above however this function returns the string of the Value at
// the desired environment node.
char	*get_env(t_env *s_env, char	*key)
{
	t_env	*tmp;

	tmp = find_env(s_env, key);
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

// free the 2 strings used in init env to save some lines.
void	free_vals(char *key, char *value)
{
	free(key);
	free(value);
}

// pull the setting of PWD and OLDPWD into a helper to clean up init env.
void	setPWD(t_env **head)
{
	char *value;
	
	value = getcwd(NULL, 0);
	if (value)
	{
		set_env(head, "PWD", value);
		set_env(head, "OLDPWD", NULL);
		free(value);
	}
}
