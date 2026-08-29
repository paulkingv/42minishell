/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:43:07 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 16:35:00 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper Function to make a New Token Node
t_token	*make_new_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void	remove_token(t_token **head, t_token *key)
{
	t_token	*current;
	t_token	*prev;

	current = *head;
	while (current)
	{
		if (current == key)
		{
			if (current == *head)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
