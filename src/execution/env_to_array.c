/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 21:04:29 by pking             #+#    #+#             */
/*   Updated: 2026/07/17 12:17:28 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file is to define a funciton that will convert the env linked list into an array.
// Each ellement in the array is the KEY and VALUE together, separated by an equals (=) sign.

#include "minishell.h"

static void	fill_array(char **array, t_env *tmp)
{
	char	*line;
	int		i;

	i = 0;
	while(tmp)
	{
		if (tmp->key)
		{
			line = ft_strjoin(tmp->key, "=");
			array[i] = ft_strjoin (line, tmp->value);
			free(line);
			i++;
			tmp = tmp->next;
		}
	}
	array[i] = NULL;
}
char	**env_to_array(t_env *env)
{
	t_env	*tmp = NULL;
	char 	**array;
	int		list_size;

	list_size = 0;
	tmp = env; // tmp is used to walk, env stays @ head
	while (tmp)
	{
		list_size++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (list_size + 1));
	if (!array)
		return (NULL);
	tmp = env; // tmp is used to walk, env stays @ head
	fill_array(array, tmp);
	return (array);
}

