/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pvoid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:24:17 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	get_length(unsigned long n, int bs)
{
	int	digit;

	digit = 0;
	if (n < 0)
		n = n * -1;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / bs;
		digit++;
	}
	return (digit);
}

static int	put_void(unsigned long n, char *base, int fd)
{
	unsigned int	i;
	unsigned int	bs;
	char			*hex;

	bs = ft_strlen(base);
	hex = base;
	i = get_length(n, bs);
	if (n >= bs)
	{
		put_void((n / bs), base, fd);
	}
	ft_printf_putchar_fd((hex[n % bs]), fd);
	return (i);
}

int	ft_printf_pvoid(unsigned long n, char *base, int fd)
{
	unsigned int	i;

	i = 0;
	if (!n)
	{
		ft_printf_putstr_fd("(nil)", fd);
		return (5);
	}
	i = ft_printf_putstr_fd("0x", fd);
	i += put_void(n, base, fd);
	return (i);
}
