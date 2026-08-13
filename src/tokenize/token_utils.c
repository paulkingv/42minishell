/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:43:07 by jfox              #+#    #+#             */
/*   Updated: 2026/08/13 17:59:23 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
