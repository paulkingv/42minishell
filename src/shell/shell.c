/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:49:32 by jfox              #+#    #+#             */
/*   Updated: 2026/08/25 00:37:36 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path(t_shell *minishell)
{
	t_shell	*tmp_shell;
	t_env	*tmp;
	char	*path;

	tmp_shell = minishell;
	tmp = find_env(tmp_shell->env, "PWD");
	if (!tmp)
	{
		ft_printf("PATH not found.");
		return (NULL);
	}
	path = tmp->value;
	return (path);
}
