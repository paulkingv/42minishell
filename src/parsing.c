/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:02:16 by jfox              #+#    #+#             */
/*   Updated: 2026/07/14 17:19:39 by jfox             ###   ########.fr       */
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

void	sort_tokens(t_cmd *cmd_current, t_token *token, int count)
{
	t_token	*tmp = NULL;
	t_cmd	*cmd = NULL;
	int		i;

	tmp = token;
	cmd = cmd_current;
	i = 0;
	cmd->args = ft_calloc(sizeof(char **), count + 1);
	while (tmp && i < count)
	{
		if (tmp->type == WORD)
		{
			cmd->args[i] = ft_strdup(tmp->value);
			i++;
		}
		// if (tmp->type == REDIR_OUT)
		// {

		// }
		// if (tmp->type == REDIR_IN)
		// {

		// }
		if (tmp->type == PIPE)
			return ;
		tmp = tmp->next;
	}
}

int	count_args(t_token *tokens)
{
	t_token	*tmp = NULL;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	t_token	*tmp = NULL;
	int	count;

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
