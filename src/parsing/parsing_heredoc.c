/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 01:17:03 by pking             #+#    #+#             */
/*   Updated: 2026/08/30 19:06:04 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Strip Quotes:
	This function is used to remove the quotes from the value
	Uses two pointers that advance at different times -- skips quotes ->
	writes insides Tracks "in quote" status -> int quote
*/
int	strip_quotes(char *value)
{
	char	in_quote;
	int		read;
	int		write;

	read = 0;
	write = 0;
	in_quote = 0;
	while (value[read])
	{
		if (!in_quote && (value[read] == '\'' || value[read] == '"'))
			in_quote = value[read++];
		else if (in_quote && value[read] == in_quote)
		{
			in_quote = 0;
			read++;
		}
		else
			value[write++] = value[read++];
	}
	value[write] = '\0';
	if (in_quote)
		return (-2);
	return (0);
}

// PK: Function to check if there are at least 2 quotes inside value.
// return (-1) error on open quotes, returns (1) on quoted, and (0) on no quotes
int	is_hd_quoted(char *value)
{
	int	squote_count;
	int	dquote_count;
	int	i;

	i = 0;
	squote_count = 0;
	dquote_count = 0;
	while (value[i])
	{
		if (value[i] == '"')
			dquote_count++;
		else if (value[i] == '\'')
			squote_count++;
		i++;
	}
	if (squote_count % 2 != 0 || dquote_count % 2 != 0)
		return (-1);
	else if (squote_count > 0 || dquote_count > 0)
		return (1);
	return (0);
}
