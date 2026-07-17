/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:44:36 by jfox              #+#    #+#             */
/*   Updated: 2026/07/17 12:22:24 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//goes thru the word until the end to find the last char
static int find_end_word(char *input, int i, int word_start)
{
	char quote_type;

	if (input[i] == '"' || input[i] == '\'')
	{
		quote_type = input[i];
		i++;
		word_start = i;
		while(input[i] && input[i] != quote_type)
			i++;
	}
	else
	{
		while (input[i] && input[i] != ' ' && input[i] != '\t'
 			&& input[i] != '|' && input[i] != '<' && input[i] != '>')
			i++;
	}
    return (i);
}

// Our Helper for get_type. Returns Enum. Single Char Checker.
static t_token_type get_type(char *value, int i)
{
	if (value[i] == '|')
		return (PIPE);
	if (value[i] == '<')
	{
		if (value[i + 1] == '<')
			return (HEREDOC);
		else
			return (REDIR_IN);
	}
	if (value[i] == '>')
	{
		if (value[i + 1] == '>')
			return (APPEND);
		else
			return (REDIR_OUT);
	}
	if (value[i] == '"' || value[i] == '\'')
	{
		if (value[i] == '"')
			return (WORD | D_QUOTED);
		else
			return (WORD | S_QUOTED);
	}
	return (WORD);
}

// Helper Function to make a New Token Node
t_token *make_new_token(t_token_type type, char *value)
{
	t_token *new_token = NULL;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

// Gonna need some helper functions here, function is too long!
t_token *tokenize(char *input)
{
	t_token *head = NULL;
	t_token *tail = NULL;
	t_token *new = NULL;
	int word_start;
	int i;

	word_start = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] >= 9 && input[i] <= 13) || input [i] == ' ')
		{
			i++;
			continue;
		}
		word_start = i;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (input[i] == '<' && input[i + 1] == '<')
				i++;
			if (input[i] == '>' && input[i + 1] == '>')
				i++;
			i++;
		}
		else
			i = find_end_word(input, i, word_start);
		new = make_new_token(get_type(input, word_start),
				ft_substr(input, word_start, i - word_start));
		if (!new)
		{
			free_tokens(&head);
			return (NULL);
		}
		if (!head)
		{
			head = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail = tail->next;
		}
	}
	return (head);
}

