/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 14:33:29 by jfox              #+#    #+#             */
/*   Updated: 2026/08/26 13:30:29 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*append_string(char *s1, char *s2)
{
	char	*tmp;

	if (!s1)
		return (NULL);
	if (!s2)
		s2 = "";
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

char	*append_char(char *string, char c)
{
	char	r[2];
	char	*tmp;

	if (!string)
		return (NULL);
	r[0] = c;
	r[1] = '\0';
	tmp = ft_strjoin(string, r);
	free(string);
	return (tmp);
}

char	*find_word(char *word)
{
	char	*ret;
	int		i;

	ret = "";
	i = 0;
	while (ft_isalnum(word[i]) || word[i] == '_')
		i++;
	i++;
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, word, i);
	return (ret);
}
