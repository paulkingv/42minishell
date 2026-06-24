/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:08:17 by jfox              #+#    #+#             */
/*   Updated: 2026/06/24 11:04:02 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
