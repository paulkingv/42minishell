/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:55:09 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (!*big)
		return (NULL);
	while (big[i] || i < len)
	{
		x = 0;
		while ((big[i + x] == little[x]) && (i + x) < len)
		{
			x++;
			if (little[x] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
