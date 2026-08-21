/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 02:31:14 by pking             #+#    #+#             */
/*   Updated: 2026/08/21 04:35:31 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int token_syntax_error(int type, t_token *clone)
{
	if (type == 1)
	{
		perror("bash: syntax error near unexpected token `|'"); //bash doesnt work like this idk 5.3
		type = 127;
	}
	else if (type == 2)
	{
		if (clone->next == NULL)
			perror("syntax error near unexpected token `|'");
		else if (clone->next->type & PIPE)
			perror("syntax error near unexpected token `||'");
		type = 2;
	}
	else if (type == 3)
	{
		if (clone->next == NULL)
			perror("syntax error near unexpected token `newline'");
		else if (clone->next->type != WORD)
			perror("syntax error near unexpected token"); // adding logic 2 this is too much
		type = 258;
	}
	return (type);
}

static int validate_tokens(t_token *token, int error) // exit value needs to get changed
{
	t_token *clone;

	clone = token;
	if (!clone)
		return (-1);
	if ((clone->type & PIPE)) //only happens first time funct runs - check pipe as first
		error = token_syntax_error (1, clone);
	while (clone) // check the rest of tokens
	{
	// first, pipe cant be last or followed by pipe
		if ((clone->type & PIPE)) // >,<,>>
		{
			if ((clone->next == NULL) || (clone->next->type & PIPE))
				error = token_syntax_error(2, clone);
		}
	// if clone == REDIR && (we are last token || next->type isnt word)
		if (((clone->type & REDIR_MASK))
		&& ((clone->next == NULL) || (clone->next->type != WORD)))
			error = token_syntax_error(3, clone);
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