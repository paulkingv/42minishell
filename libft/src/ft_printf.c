/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:37:26 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	types(const char t, va_list args)
{
	size_t	i;
	char	*hl;
	char	*hh;

	i = 0;
	hl = "0123456789abcdef";
	hh = "0123456789ABCDEF";
	if (t == 'c')
		i = ft_printf_putchar_fd(va_arg(args, int), 1);
	else if (t == 's')
		i = ft_printf_putstr_fd(va_arg(args, char *), 1);
	else if (t == 'd' || t == 'i')
		i = ft_printf_putnbr_fd(va_arg(args, int), 1);
	else if (t == 'p')
		i = ft_printf_pvoid((unsigned long)va_arg(args, const void *), hl, 1);
	else if (t == 'u')
		i = ft_printf_putnbr_unsigned_fd(va_arg(args, unsigned int), 1);
	else if (t == 'x')
		i = ft_printf_putnbr_hex_fd(va_arg(args, unsigned int), hl, 1);
	else if (t == 'X')
		i = ft_printf_putnbr_hex_fd(va_arg(args, unsigned int), hh, 1);
	else if (t == '%')
		i = ft_printf_putchar_fd('%', 1);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	size_t		len;
	size_t		i;
	va_list		args;

	len = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += types(format[i], args);
		}
		else
		{
			ft_printf_putchar_fd(format[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
