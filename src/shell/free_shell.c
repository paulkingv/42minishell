/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:21:00 by pking             #+#    #+#             */
/*   Updated: 2026/07/23 00:13:48 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int free_shell(t_shell *shell)
{
	if (!shell)
		return (0);
	if(shell->cmdline)
	{
		free_cmd(&shell->cmdline);
		shell->cmdline = NULL;
	}
	if(shell->tokens)
	{
		free_tokens(&shell->tokens);
		shell->tokens = NULL;
	}
	if(shell->env)
	{
		free_env(&shell->env);
		shell->env = NULL;
	}
	free(shell);
	return 0;
}