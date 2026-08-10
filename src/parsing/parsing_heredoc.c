/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 01:17:03 by pking             #+#    #+#             */
/*   Updated: 2026/08/09 00:34:56 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Modifies the malloc in place (VALUE)
static int replace_value(char *value, int start, int end)
{
	int i;

	i = 0;
	while (start + 1 + i < end) // character after initial quote
	{
		value[i] = value[start + 1 + i];
		i++;
	}
	value[i] = '\0';
	return (0);
}
/* Strip Quotes:
	This function is used to remove the quotes from the value 
	Uses two pointers that advance at different times -- skips quotes -> writes insides
	Tracks "in quote" status -> int quote
*/
int strip_quotes(char *value)
{
	int read;	//read index
	int write; 	//write index
	char quote;

	read = 0;  // 
	write = 0;
	in_quote = 0; // in quote state
	end = ft_strlen(value) - 1;
	while (value[read])
	{
		if (!in_quote && (value[read] == '\'' || value[read] == '"'))
			in_quote = value[read++]; // ' / " detected, and !in quote, 
		else if (in_quote && value[read] == in_quote)
		{
			in_quote = 0; // we have closed the previous quote
			read++; // move the read index
		}
		else
			value[write++] = value[read++]; // if any character, in quote or not (cant be quote itself, unless inside quote
	}
	value[write] == '\0';
	if (quote)
		return (-2); // defensive: case where we have an open quote
	return (0);
}

// PK: Function to check if there are at least 2 quotes inside value. 
// return (-1) error on open quotes, returns (1) on quoted, and (0) on no quotes
int	is_hd_quoted(char *value)
{
	int squote_count;
	int dquote_count;
	int i;
	
	i = 0;
	squote_count = 0;
	dquote_count = 0;
	while (value[i])
	{
		if(value[i] == '"')
			dquote_count++;
		else if (value[i] == '\'')
			squote_count++;
		i++;
	}
	if (squote_count % 2 != 0 || dquoute_count % 2 != 0)
		return (-1); // there was an open quote
	else if (squote_count > 0 || dquote_count > 0)
		return (1); // quotes, and were closed
	return (0);
}