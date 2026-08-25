/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 00:16:35 by j.fox             #+#    #+#             */
/*   Updated: 2026/08/26 00:16:35 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// display error for needing a numeric argument
// bypass the error in edge cases
void	require_number(t_shell *shell, char *arg)
{
	if (!ft_strcmp(arg, "--"))
	{
		shell->exit	= 0;
		return ;
	}
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	shell->status = 1;
	shell->exit	= 2;
	return ;
}

// helper to bypass whitespace and move the pointer of i, saving lines
// kicking myself for not making this sooner
void	handle_whitespace(char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		*i = *i + 1;
	return ;
}

// determine the size of an unsigned long long
t_ull	find_limit(int sign)
{
	if (sign == -1)
		return ((unsigned long long)LLONG_MAX + 1);
	else
		return (LLONG_MAX);
}

// helper to set the sign if we have to deal with a negative
int	set_sign(char c, int *i)
{
	int	sign;

	sign = 1;
	if (c == '-')
		sign = -1;
	*i = *i + 1;
	return (sign);
}
