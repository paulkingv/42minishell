/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_fieldexpansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:27:31 by jfox              #+#    #+#             */
/*   Updated: 2026/08/30 15:17:57 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in expansion, while expanding a long string, we need to find the end of the
// field so we can put it into it's own token/value
static int	find_field_end(char *str, int i)
{
	while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
		i += 1;
	return (i);
}

// function skips whitespace in a long variable expansion and then finds each
// field or word within it
static char	*get_field(char *str, int *i)
{
	int		start;
	int		end;
	char	*ret;

	handle_whitespace(str, i);
	start = *i;
	end = find_field_end(str, *i);
	ret = ft_substr(str, start, end - start);
	*i = end;
	return (ret);
}

// split the string on whitespace into new values, make tokens and add them in
// order to a chained list. This list will be copied into shell later.
void	split_expansion(t_exp *fields, char *str)
{
	int		i;
	char	*field;
	t_token	*new;

	i = 0;
	while (str[i])
	{
		field = get_field(str, &i);
		if (!field)
			return ;
		new = make_new_token(WORD, field);
		if (!new)
		{
			free(field);
			return ;
		}
		token_add_back(&fields->tokens, new);
	}
	return ;
}

// run through all the options of expansion seeing if need to split the value
// on white space or if we simply append the string.
void	field_expansion(t_exp *fields, char *tmp)
{
	if (has_whitespace(tmp))
	{
		split_expansion(fields, tmp);
		if (fields->tokens)
			fields->string = ap_string(fields->string, fields->tokens->value);
	}
	else
		fields->string = ap_string(fields->string, tmp);
	return ;
}
