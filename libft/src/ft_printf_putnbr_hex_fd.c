/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_hex_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:02:24 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	get_length(unsigned int n, int bs)
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

int	ft_printf_putnbr_hex_fd(unsigned int n, char *base, int fd)
{
	unsigned int	i;
	unsigned int	bs;
	char			*hex;

	bs = ft_strlen(base);
	hex = base;
	i = get_length(n, bs);
	if (n >= bs)
	{
		ft_printf_putnbr_hex_fd((n / bs), base, fd);
	}
	ft_printf_putchar_fd((hex[n % bs]), fd);
	return (i);
}
