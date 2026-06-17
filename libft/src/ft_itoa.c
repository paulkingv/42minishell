/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:59:51 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	get_length(int n)
{
	int	digit;
	int	nmb;

	digit = 0;
	nmb = n;
	if (nmb == 0)
		return (1);
	while (nmb > 0)
	{
		nmb = nmb / 10;
		digit++;
	}
	return (digit);
}

static char	*get_number(char *str, int n, int nlength)
{
	int	num;
	int	len;

	num = n;
	len = nlength;
	while (len--)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		nlength;
	char	*str;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	sign = 0;
	if (n < sign)
	{
		sign = 1;
		n = n * -1;
	}
	nlength = (get_length(n) + sign);
	str = (char *)ft_calloc((nlength + 1), sizeof(char));
	if (!str)
		return (NULL);
	str = get_number(str, n, nlength);
	if (sign == 1)
		str[0] = '-';
	return (str);
}
