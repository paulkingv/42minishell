/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:48 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	x;
	char	*result;

	if (!s)
		return (NULL);
	i = start;
	x = 0;
	if (start >= ft_strlen(s))
	{
		result = (char *)ft_calloc(1, sizeof(char));
		return (result);
	}
	if (len > ft_strlen(s) - start)
		len = (ft_strlen(s) - start);
	result = (char *)ft_calloc((len) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (s[x] && x < len)
	{
		result[x] = s[i + x];
		x++;
	}
	return (result);
}
