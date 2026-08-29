/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_fieldexpansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:27:31 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 19:45:40 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in expansion, while expanding a long string, we need to find the end of the
// field so we can put it into it's own token/value
int	find_field_end(char *str, int i)
{
	while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
		i += 1;
	return (i);
}

// function skips whitespace in a long variable expansion and then finds each
// field or word within it
char	*get_field(char *str)
{
	int		start;
	int		end;
	char	*ret;

	start = 0;
	handle_whitespace(str, &start);
	end = find_field_end(str, start);
	ret = ft_substr(str, start, end - start);
	return (ret);
}

char	*split_expansion(char *str)
{
	char	*field;

	field = get_field(str);
	return(field);
}

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
