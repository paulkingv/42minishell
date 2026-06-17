/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:50:23 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = ft_strlen(src);
	if (size == 0)
	{
		return (x);
	}
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (x);
}
