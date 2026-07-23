/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:49:32 by jfox              #+#    #+#             */
/*   Updated: 2026/07/21 16:53:17 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_shell	*shell_init(char **envp)
// {
// 	t_shell	*shell = NULL;
// 	t_token	*tokens = NULL;
// 	t_cmd	*cmdline = NULL;

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (NULL);
// 	shell->env = init_env(envp);
// 	shell->tokens = tokens;
// 	shell->cmdline = cmdline;
// 	shell->status = 1;
// 	shell->exit = 0;
// 	return (shell);
// }

char	*ft_path(t_shell *minishell)
{
	t_shell	*tmp_shell =NULL;
	t_env	*tmp = NULL;
	char	*path;

	tmp_shell = minishell;
	tmp = find_env(tmp_shell->env, "PATH");
	if (!tmp)
	{
		ft_printf("PATH not found.");
		return (NULL);
	}
	path = tmp->value;
	return (path);
}
