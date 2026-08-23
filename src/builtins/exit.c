/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 17:17:53 by j.fox             #+#    #+#             */
/*   Updated: 2026/08/21 17:17:53 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_number(char *str, long long *result)
{
	unsigned long long	n;
	unsigned long long	limit;
	int					sign;
	int					i;
	int					digit;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	if (sign == -1)
		limit = (unsigned long long)LLONG_MAX + 1;
	else
		limit = LLONG_MAX;
	while (ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		if (n > (limit - digit) / 10)
			return (0);
		n = (n * 10) + digit;
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i])
		return (0);
	if (sign == -1 && n == (unsigned long long)LLONG_MAX + 1)
		*result = LLONG_MIN;
	else
		*result = (long long)n * sign;
	return (1);
}

static void  require_number(t_shell *shell, char *arg)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
    shell->status = 1;
    shell->exit	= 2;
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
	if (!check_number(tmp->args[1], &val))
    {
        require_number(shell, tmp->args[1]);
		return (2);
    }
	if (tmp->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit	= 1;
		return (1);
	}
	shell->status = 1;
	shell->exit = (unsigned char)val;
	return (shell->exit);
}
