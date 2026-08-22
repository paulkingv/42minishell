/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 02:31:14 by pking             #+#    #+#             */
/*   Updated: 2026/08/22 00:29:36 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void token_syntax_error (t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->type == NULL)
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2); 
		else

		type = 127;
	}
	else
	{
		if(token->next == NULL)
			ft_putstr_fd("syntax error near unexpected token `newline'\n");
		else
		{
			ft_putstr_fd("syntax error near unexpected token `")
			ft_putstr_fd(token->next->value, 2);
		}
		if (token->next != NUll)
			ft_putstr_fd("'\n", 2);
	}
}

static int validate_tokens(t_token *token) // exit value needs to get changed
{
	t_token *clone;

	clone = token;
	if (!clone)
		return (-1);
	if ((clone->type & PIPE)) //only happens first time funct runs - check pipe as first
		error = token_syntax_error (clone);
	while (clone) // check the rest of tokens
	{
	// first, pipe cant be last or followed by pipe
		if ((clone->type & PIPE)) // >,<,>>
		{
			if ((clone->next == NULL) || (clone->next->type & PIPE))
				error = token_syntax_error(clone);
		}
	// if clone == REDIR && (we are last token || next->type isnt word)
		if (((clone->type & REDIR_MASK))
		&& ((clone->next == NULL) || (clone->next->type != WORD)))
			error = token_syntax_error(clone);
		clone = clone->next;
	}
	return (error);
}

int token_validation(t_token *token, t_shell *shell)
{
	int error;

	error = 0;
	error = validate_tokens(token, error);
	shell->exit = error;
	if (error != 0)
		return (1);
	else
		return (0);
}