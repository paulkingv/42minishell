/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:21:00 by pking             #+#    #+#             */
/*   Updated: 2026/08/17 15:42:41 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// changed the structure of shell in main.
// meaning there is no memory to free for the shell.
// commented out free shell for the time being.
int	free_shell(t_shell *shell)
{
	if (shell->cmdline)
	{
		free_cmd(&shell->cmdline);
		shell->cmdline = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(&shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->env)
	{
		free_env(&shell->env);
		shell->env = NULL;
	}
	return (0);
}
