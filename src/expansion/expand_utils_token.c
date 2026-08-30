/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 01:35:47 by j.fox             #+#    #+#             */
/*   Updated: 2026/08/30 01:35:47 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// move through a token list and return a pointer to the last one
t_token	*token_last(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

// using the last token in a list, append a char to that tokens value
void	append_to_last_token(t_exp *fields, char c)
{
	t_token	*last;

	last = token_last(fields->tokens);
	last->value = append_char(last->value, c);
	return ;
}

// build a tempory token list of all the field split variables
void	token_add_back(t_token **head, t_token *new_node)
{
	t_token	*tmp;

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
