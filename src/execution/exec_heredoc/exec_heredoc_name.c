/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:23:28 by pking             #+#    #+#             */
/*   Updated: 2026/08/30 20:06:03 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// passes stack mem addr to val as long
static long	random_long_gen(void)
{
	static long	counter;
	int			stack_var;
	long		val;

	counter++;
	val = (long)&stack_var;
	val = (val ^ counter) & 0x7FFFFFFFL;
	return (val);
}

// HD_NAME is used to gen a random* name for the HD
// Now uses a random long generator
char	*hd_name(int *fd)
{
	char	*num;
	char	*filename;
	int		tries;

	tries = -1;
	while (++tries < 100)
	{
		num = ft_itoa(random_long_gen());
		if (!num)
			return (NULL);
		filename = ft_strjoin("./heredoc_", num);
		if (!filename)
			return (NULL);
		*fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (*fd > 0)
		{
			free(num);
			return (filename);
		}
		free(num);
		free(filename);
	}
	return (NULL);
}
