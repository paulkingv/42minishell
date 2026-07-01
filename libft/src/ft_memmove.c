/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:30:29 by jfox              #+#    #+#             */
/*   Updated: 2026/06/24 11:04:02 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ftdest;
	unsigned char	*ftsrc;

	ftdest = (unsigned char *)dest;
	ftsrc = (unsigned char *)src;
	if (dest <= src)
	{
		while (n--)
			*ftdest++ = *ftsrc++;
	}
	else if (dest > src)
	{
		ftdest += n - 1;
		ftsrc += n - 1;
		while (n--)
			*ftdest-- = *ftsrc--;
	}
	return (dest);
}
