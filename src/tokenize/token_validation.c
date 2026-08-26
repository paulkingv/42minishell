/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 02:31:14 by pking             #+#    #+#             */
/*   Updated: 2026/08/26 12:45:31 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void token_syntax_error (t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->next == NULL)
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		else
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	}
	else
	{
		if(token->next == NULL)
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		else
		{
			ft_putstr_fd("syntax error near unexpecte fd token `", 2);
			ft_putstr_fd(token->next->value, 2);
		}
		if (token->next != NULL)
			ft_putstr_fd("'\n", 2);
	}
}

static int validate_tokens(t_token *token) // exit value needs to get changed
{
	t_token *clone;

	clone = token;
	while (clone) // check the rest of tokens
	{
	// pipe cant be last or first or followed by pipe
		if (clone->type == PIPE && (clone == token || clone->next == NULL )) //check: Node 1 = PIPE; Node[i+1] = PIPE; NULL
		{
				token_syntax_error(clone);
				return (1);
		}
	// if clone == REDIR && (we are last token || next->type isnt word)
		if ((clone->type & (REDIR_OUT | REDIR_IN | APPEND | HEREDOC) //REDIR_MASK)
		&& (clone->next == NULL || clone->next->type != WORD)))
		{
			token_syntax_error(clone);
			return (1);
		}
		clone = clone->next;
	}
	return (0);
}

int token_validation(t_token *token, t_shell *shell)
{
	if (validate_tokens(token))
	{
		shell->exit = 2;
		return (1);
	}
		return (0);
}
