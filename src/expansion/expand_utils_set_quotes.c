/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_set_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 13:37:30 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 16:44:35 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// confirms simply if the word specifically is quoted
int	is_quoted(char *word)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

// simple helper to set quote bools to 0 or 1 depending on the char recieved
// this is critical following the execution of this function as it helps us
// determine if strings are literal or need expanding
int	set_quotes(char c, int *dquote, int *squote)
{
	if (c == '\'' && !*dquote)
	{
		*squote = !*squote;
		return (1);
	}
	else if (c == '"' && !*squote)
	{
		*dquote = !*dquote;
		return (1);
	}
	return (0);
}
