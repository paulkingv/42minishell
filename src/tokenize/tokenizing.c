/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:44:36 by jfox              #+#    #+#             */
/*   Updated: 2026/08/24 23:18:50 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* WORKING VERSION: */
// 		Desc:
//			This function will "tokenize" the input array.
//			It does this by separating based on the space.
//			Returns the LL of args (including quotes).
//goes thru the word until the end to find the last char
static int	find_end_word(char *input, int i)
{
	char	quote_type;

	while (input[i] && input[i] != ' ' && input[i] != '\t' && input[i] != ';'
			&& input[i] != '|' && input[i] != '<' && input[i] != '>')
	{
		if ((input[i] == '"' || input[i] == '\''))
		{
			quote_type = input[i];
			i++;
			while (input[i] && input[i] != quote_type)
				i++;
			if (!input[i])
				return (-1); //unclosed quote error
			i++; //fixes the i to be at index outside the quotes
		}
		else
				i++;
	}
	return (i);
}

// Our Helper for get_type. Returns Enum. Single Char Checker.
static t_token_type	get_type(char *value, int i)
{
	if (value[i] == '|')
		return (PIPE);
	if (value[i] == ';')
		return (SEMICOLON);
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
	return (WORD);
}

// NEW HELPER: Build Token (From Refactor)
// Builds one token starting at *i
// NULL on syntax/allocation error

static t_token *build_token(char *input, int *i, t_shell *shell, t_token *new)
{
	int word_start;

	word_start = *i;
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>' 
		|| input[*i] == ';')
	{
		if (input[*i] == '<' && input[*i + 1] == '<')
			i++;
		if (input[*i] == '>' && input[*i + 1] == '>')
			(*i)++;
		(*i)++;
	}
	else
	{
		*i = find_end_word(input, *i);
		if(*i == -1)
		{
			ft_putstr_fd("unexpected EOF while looking for matching quote\n", 2);
			shell->exit = 2;
			return (NULL); // Unclosed quote edge case. Normally opens dsquote doc
		}
	}
	new = (make_new_token(get_type(input, word_start), ft_substr(input, word_start, *i - word_start)));
	return (new); //(new)
}

// Helper to make one command to loop
static int tokenize_loop(char *input, t_token **head, t_shell *shell)
{
	int	i;
	t_token *tail;
	t_token *new;

	i = 0;
	tail = NULL;
	while (input[i])
	{
		while ((input[i] >= 9 && input[i] <= 13) || input [i] == ' ')
			i++;
		if (!input[i])
			break ;
		new = build_token(input, &i, shell, new);
		if (!new)
			return (-1);
		if (!*head)
			*head = new;
		else
			tail->next = new;
		tail = new;
	}
	return (0);
} 


// Tokenize input into an LL of tokens
t_token	*tokenize(char *input, t_shell *shell)
{
	t_token *head;

	head = NULL;
	if (!input)
		return (NULL);
	if (tokenize_loop(input, &head, shell) == -1)
	{
		free_tokens(&head);
		return (NULL);
	}
	if (token_validation(head, shell)) //if error in syntax
	{
		free_tokens(&head);
		return (NULL);
	}
	return (head);
}
