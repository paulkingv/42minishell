/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:08:17 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	buf;
	void	*ptr;

	if (size > 0 && nmemb * size / size != nmemb)
		return (NULL);
	buf = nmemb * size;
	ptr = malloc(buf);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, buf);
	return ((void *)ptr);
}
