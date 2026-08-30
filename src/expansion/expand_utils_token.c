/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 01:35:47 by j.fox             #+#    #+#             */
/*   Updated: 2026/08/30 15:09:37 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// simple detection for whitespace
int	has_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

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

	if (!fields || !fields->tokens)
		return ;
	last = token_last(fields->tokens);
	if (!last)
		return ;
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

// handed a chained list of tokens this function copies one list of tokens
// into another in the order and place they show up
void	splice_tokens(t_token *ttok, t_token *new_tokens)
{
	t_token	*first;
	t_token	*rest;
	t_token	*last;

	if (!ttok || !new_tokens)
		return ;
	first = new_tokens;
	rest = first->next;
	free(first->value);
	free(first);
	if (!rest)
		return ;
	last = rest;
	while (last->next)
		last = last->next;
	last->next = ttok->next;
	ttok->next = rest;
}
