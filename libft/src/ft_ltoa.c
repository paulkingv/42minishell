/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 00:57:52 by pking             #+#    #+#             */
/*   Updated: 2026/08/26 11:42:34 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*n_is_zero(long n, char *str)
{
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	return (str);
}

static char	*reverse_str(char *str)
{
	int		start;
	int		end;
	char	tmp;

	start = 0;
	end = (ft_strlen(str) - 1);
	while (start < end)
	{
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;
		start++;
		end--;
	}
	return (str);
}

static void	process_ltoa(long *n, char *str, int i, int is_negative)
{
	while (*n > 0)
	{
		str[i++] = '0' + (*n % 10);
		*n = *n / 10;
	}
	if (is_negative)
		str[i++] = '-';
	str[i] = '\0';
	reverse_str(str);
}

/* 19 is long max digit*/
char	*ft_ltoa(long n)
{
	char	*str;
	int		i;
	int		is_negative;

	i = 0;
	is_negative = 0;
	if (n < 0)
	{
		is_negative = 1;
		n = -n;
	}
	str = malloc(21);
	if (!str)
		return (NULL);
	n_is_zero(n, str);
	while (n != 0)
		process_ltoa(&n, str, i, is_negative);
	return (str);
}
