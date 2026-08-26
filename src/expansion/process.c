/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:43:21 by jfox              #+#    #+#             */
/*   Updated: 2026/08/25 12:50:39 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// saves lines in main by building a function to handle expand and then parse.
// possible need to change parse to take the whole shell and not just tokens.
int	process(t_shell *shell, t_token *tokens)
{
	if (expand_tokens(shell, tokens, NULL, NULL))
		return (1);
	shell->cmdline = parse(shell, NULL, NULL, NULL);
	if (!shell->cmdline)
		return (1);
	return (shell->exit);
}