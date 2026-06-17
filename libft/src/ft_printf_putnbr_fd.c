/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:02:24 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	get_length(int n)
{
	int	digit;

	digit = 0;
	if (n < 0)
	{
		digit++;
		n = n * -1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

int	ft_printf_putnbr_fd(int n, int fd)
{
	int	i;

	if (n == -2147483648)
	{
		ft_printf_putstr_fd("-2147483648", fd);
		return (11);
	}
	i = get_length(n);
	if (n < 0)
	{
		ft_printf_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_printf_putnbr_fd((n / 10), fd);
	}
	ft_printf_putchar_fd(((n % 10) + '0'), fd);
	return (i);
}
