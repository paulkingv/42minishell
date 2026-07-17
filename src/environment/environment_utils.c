/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:38:11 by jfox              #+#    #+#             */
/*   Updated: 2026/07/17 12:40:08 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// As with all structs, a handle to create the node for a chained list.
// Here we also pass information so we can fill the struct while we initialize it.
t_env	*new_env(char *key, char *value)
{
	t_env	*new = NULL;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

// A simply string compare helper to check if the current environment variable
// is the one we are looking for, it returns a pointer to the desired variable.
t_env	*find_env(t_env *s_env, char *key)
{
	t_env	*tmp;
	int		i;

	//consider what you're looking for, key length or similar evn names can causes issues here
	tmp = s_env;
	i = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, i) != 0)
			tmp = tmp->next;
		else
			return(tmp);
	}
	return (NULL);
}

// Similar to above however this function returns the string of the Value at the
// desired environment node.
char	*get_env(t_env *s_env, char	*key)
{
	t_env	*tmp;
	int		i;

	//consider what you're looking for, key length or similar evn names can causes issues here
	tmp = s_env;
	i = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, i) != 0)
			tmp = tmp->next;
		else
			return(tmp->value);
	}
	return (NULL);
}