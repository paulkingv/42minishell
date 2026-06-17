/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:03:02 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	x;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[i]))
		i++;
	x = (ft_strlen(s1) - 1);
	while (ft_strrchr(set, s1[x]))
		x--;
	trimmed = ft_substr(s1, i, (x - i + 1));
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
