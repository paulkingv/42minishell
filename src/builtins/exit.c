/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 17:17:53 by j.fox             #+#    #+#             */
/*   Updated: 2026/08/26 11:48:21 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this is the ugliest atoll i've ever seen
static int	check_number(char *str, long long *result, int sign, int i)
{
	unsigned long long	n;
	unsigned long long	limit;

	n = 0;
	handle_whitespace(str, &i);
	if (str[i] == '+' || str[i] == '-')
		sign = set_sign(str[i], &i);
	if (!ft_isdigit(str[i]))
		return (0);
	limit = find_limit(sign);
	while (ft_isdigit(str[i]))
	{
		if (n > (limit - (str[i] - '0')) / 10)
			return (0);
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	handle_whitespace(str, &i);
	if (str[i])
		return (0);
	if (sign == -1 && n == (unsigned long long)LLONG_MAX + 1)
		*result = LLONG_MIN;
	else
		*result = (long long)n * sign;
	return (1);
}

// exit with no options
int	ft_exit(t_shell *shell)
{
	t_cmd		*tmp;
	long long	val;

	tmp = shell->cmdline;
	if (!tmp->args[1])
	{
		shell->status = 1;
		return (shell->exit);
	}
	if (!check_number(tmp->args[1], &val, 1, 0))
	{
		require_number(shell, tmp->args[1]);
		return (shell->exit);
	}
	if (tmp->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit = 1;
		return (shell->exit);
	}
	shell->status = 1;
	shell->exit = (unsigned char)val;
	return (shell->exit);
}
