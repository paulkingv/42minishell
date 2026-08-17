/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:02:16 by jfox              #+#    #+#             */
/*   Updated: 2026/08/17 13:14:59 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// As per most structs, helper function to create the function and alloc memory.
static t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redirections = NULL;
	new->next = NULL;
	return (new);
}

// Quick helper to count the number of arguments in the token struct.
// This is used by parse to jump through the command looking for pipes,
// This lets us break commands into seperate command structs.
static int	count_args(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		// claude suggested this ⬇️
		if (tmp->type == WORD) // only count words
			i++;
		tmp = tmp->next;
	}
	return (i);
}

// No error handling also, although some protections are here.
// Here we take an empty command struct and start to fill it with either
// arguments or Redirects.
// We store words and other arguments in the ARGS, and Redirects in the
// Redirections using the sort redirects function.
// If we hit a pipe we break out of this function as that means the command
// is finished.
static void	sort_tokens(t_cmd *cmd_current, t_token *token, int count)
{
	t_token	*tmp;
	t_cmd	*cmd;
	int		i;

	tmp = token;
	cmd = cmd_current;
	i = 0;
	cmd->args = ft_calloc(sizeof(char **), count + 1);
	if (!cmd->args)
		return ;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			cmd->args[i] = ft_strdup(tmp->value);
			i++;
		}
		if (tmp->type == REDIR_OUT || tmp->type == REDIR_IN
			|| tmp->type == APPEND || tmp->type == HEREDOC)
			sort_redirections(cmd, &tmp);
		if (tmp->type == PIPE)
			return ;
		tmp = tmp->next;
	}
}

// No real edge case or error handling.
// This function takes our list of tokens and starts building them into command
// structs.It creates a head if one does not already exist (it shouldn't) and
// then starts to fill that head by moving through the token chained list.
// Sort tokens does the bulk of the work, it fills command structs with data.
// This function is simply to build command structs and move through a list.
t_cmd	*parse(t_token *tokens, t_cmd *head, t_cmd *current, t_token *tmp)
{
	int		count;

	tmp = tokens;
	head = new_cmd();
	if (!head)
		return (NULL);
	current = head;
	while (tmp)
	{
		count = count_args(tmp);
		sort_tokens(current, tmp, count);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp)
		{
			tmp = tmp->next;
			current->next = new_cmd();
			if (!current->next)
				return (NULL);
			current = current->next;
		}
	}
	return (head);
}
