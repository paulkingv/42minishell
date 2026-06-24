/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmental.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 17:04:19 by jfox              #+#    #+#             */
/*   Updated: 2026/06/24 18:27:33 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	int		i;
	int		x;
	char	*key;
	char	*value;
	t_env	*head = NULL;
	t_env	*new = NULL;
	t_env	*tmp = NULL;

	while (*envp)
	{
		i = 0;
		x = 0;
		while ((*envp)[i] && (*envp)[i] != '=')
			i++;
		key = ft_substr((*envp), x, i);
		i++;
		x = i;
		while ((*envp)[i] != '\0')
			i++;
		value = ft_substr((*envp), x, i);
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->key = key;
		new->value = value;
		new->next = NULL;
		if (!head)
		{
			head = new;
			tmp = new;
		}
		else
			tmp->next = new;
		tmp = new;
		envp++;
	}
	return (head);
}

char	*get_env(t_env *s_env, char	*key)
{
	// make a tmp s_env before moving through the chained lists
	int	i;

	i = ft_strlen(key);
	while (s_env)
	{
		if (ft_strncmp(s_env->key, key, i) != 0)
			s_env = s_env->next;
		else
			return(s_env->value);
	}
	return (NULL);
}
