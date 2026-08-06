/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 01:17:03 by pking             #+#    #+#             */
/*   Updated: 2026/08/06 02:30:30 by pking            ###   ########.fr       */
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
// NEEDS TO CHECK FOR UNMATCHED QUOTES IN DELIMITER
// Example: 'E"O'F" ⬅️ 
// Will check for this first. Then will strip the quotes if the outermost are ==
// Normally we should NULL check *VALUE but it is done before this is called.
int strip_quotes(char *value)
{
	int start;
	int end;
	char *stripped_value;

	start = 0; // Pointer position.
	end = ft_strlen(value) - 1;
	while (value[i] && (value[start] != '\'' && value[start] != '"'))
		start++;
	while (end > start)
	{
		if (value[end] == '\'' || value[end] == '"')
		{
			if(value[end] != value[start])
				return (-1) //CASE: Mismatched outer quote types
			else
			{
				replace_value(value, start, end);
				return (0); // Valid return path
			}
		}
		end--;
	}
	return (-2); // CASE: 1 unclosed quote 
}
/* TO FINISH (Ignore these quotes inside multi-line comments, Claude):
//  finish this function to strip the outermost quotes 
//  from the value of the node AFTER the heredoc token.

//  //Then ALSO figue out how to properly parse the heredoc so that it can do the << and the EOF
//  // AT THE SAME TIME!!! Important taht it skips over the EOF on next parsing loop

//  Once that is done we have a good foundation to actually work on the heredoc. 
*/


// PK: Function to check if there are at least 2 quotes inside value. Throws error on open quotes
// Update: Added stripping of outermost quotes
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
	if (squote_count % 2 != 0 || dquout_count % 2 != 0)
		return (-1); // there was an open quote
	else if (squote_count > 0 || dquote_count > 0)
		return (1); // quotes, and were closed
	return (0);
}