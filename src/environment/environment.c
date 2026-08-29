/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 17:04:19 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 13:25:14 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A helper for set env, that actually edits the value.
t_env	*edit_env(t_env *s_env, char *key, char *new_node)
{
	t_env	*tmp;

	tmp = find_env(s_env, key);
	if (!tmp)
		return (NULL);
	free(tmp->value);
	if (new_node)
		tmp->value = ft_strdup(new_node);
	else
		tmp->value = NULL;
	return (tmp);
}

// Change the value of an environment variable using find and a new string.
// This will be used by export when we do the built ins.
void	set_env(t_env **s_env, char *key, char *value)
{
	t_env	*tmp;

	tmp = find_env(*s_env, key);
	if (tmp)
		edit_env(tmp, key, value);
	else
	{
		tmp = new_env(key, value);
		if (tmp)
			env_add_back(s_env, tmp);
	}
	return ;
}

// Allows you to remove an environment variable by freeing the data sorted there
// Then we make the previous node point to the next node.
void	unset_env(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (current == *head)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	return ;
}

// A simple function to add new data to a chained list.
// We first fill head if it doesnt exist. Then subsequent calls will move to
// the end of the chained list and place a node there.
void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

// Here we go through the string envp and break it into key and value.
// Cutting it using the = sign in the envp.
// See above for new_env and env_add back.
t_env	*init_env(char **envp, t_shell *shell, t_env *head, t_env *new)
{
	if (!envp || !envp[0])
		setpwd(&head);
	while (*envp)
	{
		get_key_value(shell, envp);
		if (!shell->key || !shell->value)
		{
			free_vals(shell->key, shell->value);
			return (NULL);
		}
		new = new_env(shell->key, shell->value);
		env_add_back(&head, new);
		free_vals(shell->key, shell->value);
		envp++;
	}
	return (head);
}
