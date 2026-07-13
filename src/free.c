/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 11:47:01 by jfox              #+#    #+#             */
/*   Updated: 2026/07/13 12:18:18 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*current = NULL;
	t_token	*next = NULL;

	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_env(t_env **s_env)
{
	t_env	*current = NULL;
	t_env	*next = NULL;

	current = *s_env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_cmd(t_cmd **cmdline)
{
	t_cmd	*current = NULL;
	t_cmd	*next = NULL;
	int		i;

	current = *cmdline;
	while (current)
	{
		i = 0;
		next = current->next;
		while (current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		free(current->redirections);
		free(current);
		current = next;
	}
}
