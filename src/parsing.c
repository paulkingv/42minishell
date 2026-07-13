/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:02:16 by jfox              #+#    #+#             */
/*   Updated: 2026/07/13 11:56:02 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Here we will start working on parsing through the tokens we have been given.

t_cmd	*new_cmd(void)
{
	t_cmd	*new = NULL;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redirections = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*sort_tokens(t_cmd *cmd_ready, t_token *token, int count)
{
	t_token	*tmp = NULL;
	t_cmd	*cmd = NULL;
	int		i;

	tmp = token;
	cmd = cmd_ready;
	i = 0;
	cmd->args = ft_calloc(sizeof(char **), count + 1);
	while (tmp && i < count)
	{
		// loop through token struct
		// check each 'type'it holds. Currently sorting word type into args.
		// ignore redirects for now. So "echo hello world" will be 3 word types and be sorted into
		// cmd_ready->args[0]echo, args[1]hello, args[2]world, args[3]NULL.
		if (tmp->type == WORD)
		{
			cmd->args[i] = ft_strdup(tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	return (cmd);
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*cmd_ready = NULL;
	t_token	*tmp = NULL;
	int	count;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	cmd_ready = new_cmd();
	if (!cmd_ready)
		return (NULL);
	cmd_ready = sort_tokens(cmd_ready, tokens, count);
	return (cmd_ready);
}
