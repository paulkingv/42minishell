/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 02:31:14 by pking             #+#    #+#             */
/*   Updated: 2026/08/29 12:52:31 by pking            ###   ########.fr       */
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

static int is_bad_separator(t_token *head, t_token *clone)
{
	// pipe cant be last or first or followed by pipe
	if (clone->type == PIPE && (clone == head || clone->next == NULL 
		|| clone->next->type == PIPE)) //check: Node 1 = PIPE; Node[i+1] = PIPE; NULL
		return (1);
	if (!ft_strcmp (clone->value, ";"))
		return (1);
	return (0);
}

static int validate_tokens(t_token *token) // exit value needs to get changed
{
	t_token *clone;

	clone = token;
	while (clone) // check the rest of tokens
	{
		if (is_bad_separator(token, clone))
		{
			token_syntax_error(clone);
			return (1);
		}
	// if clone == REDIR && (we are last token || next->type isnt word)
		if ((clone->type & (REDIR_OUT | REDIR_IN | APPEND | HEREDOC) //REDIR_MASK
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

// Helper Function to make a New Token Node
t_token	*make_new_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}
