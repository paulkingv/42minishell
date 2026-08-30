/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:44:36 by jfox              #+#    #+#             */
/*   Updated: 2026/08/30 19:26:42 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* DESCRIPTION: */
//			This function will "tokenize" the input array.
//			It does this by separating based on the space.
//			Returns the LL of args (including quotes).
//			goes thru the word until the end to find the last char

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

static int	token_end(char *input, int i, t_shell *shell)
{
	if (input[i] == '|' || input[i] == '<' 
		|| input[i] == '>' || input[i] == ';')
	{
		if ((input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
			i++;
		return (i + 1);
	}
	i = find_end_word(input, i);
	if (i == -1)
	{
		ft_putstr_fd("unexpected EOF while looking for matching quote\n", 2);
		shell->exit = 2;
	}
	return (i);
}

static int next_token(char *input, int *i, t_token **head, t_shell *shell)
{
	int		word_start;
	t_token	*new;

	while ((input[*i] >= 9 && input[*i] <= 13) || input[*i] == ' ')
		(*i)++;
	if (!input[*i])
		return (0);
	word_start = *i;
	*i = token_end(input, *i, shell);
	if (*i == -1)
		return (-1);
	new = make_new_token(get_type(input, word_start),
			ft_substr(input, word_start, *i - word_start));
	if (!new)
		return (-1);
	token_add_back(head, new);
	return (0);
}
// Tokenize input into an LL of tokens
/* REWORK PLAN */
/*
Remove the inits being passed
Instead set up the pointers inside a new init function
Add the shell struct to the tokenize function
Change the prototype
Rework the call to the verification so that it takes the shell struct

*/
t_token	*tokenize(char *input, t_shell *shell)
{
	int	i;
	t_token *head;
	int		result;

	i = 0;
	head = NULL;
	if (!input)
		return (NULL);
	while (input[i])
	{
		result = next_token(input, &i, &head, shell);
		if (result == -1)
		{
			free_tokens(&head);
			return (NULL);
		}
	}
	if (token_validation(head, shell))
	{
		free_tokens(&head);
		return (NULL);
	}
	return (head);

}
