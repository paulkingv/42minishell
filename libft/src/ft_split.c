/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:15:53 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 1;
	if (!*s)
		return (i);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			x++;
		i++;
	}
	if (s[i - 1] == c)
		x--;
	return (x);
}

static size_t	my_strlen(char const *s, char c, int i)
{
	size_t	x;

	x = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			x++;
		}
		if (s[i] == c)
		{
			return (x);
		}
		i++;
	}
	return (x);
}

static void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return ;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		x;
	char	**strings;

	if (!s)
		return (NULL);
	i = 0;
	x = 0;
	strings = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!strings)
		return (NULL);
	while (s[i] && x < count_words(s, c))
	{
		while (s[i] == c)
			i++;
		strings[x] = ft_substr(s, i, my_strlen(s, c, i));
		if (!strings[x])
		{
			free_strings(strings);
			return (NULL);
		}
		i += my_strlen(s, c, i);
		x++;
	}
	return (strings);
}
