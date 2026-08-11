/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:43:21 by jfox              #+#    #+#             */
/*   Updated: 2026/08/11 12:17:12 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// saves lines in main by building a function to handle expand and then parse.
// possible need to change parse to take the whole shell and not just tokens.
int		process(t_shell *shell, t_token *tokens)
{
	if (expand_tokens(shell, tokens))
		return (1);
	shell->cmdline = parse(shell->tokens, NULL, NULL, NULL);
	if (!shell->cmdline)
		return (1);
	return (0);
}