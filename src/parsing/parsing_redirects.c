/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:44:29 by jfox              #+#    #+#             */
/*   Updated: 2026/07/16 12:47:48 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*new_redir(char *value, t_token_type num)
{
	t_redir *new = NULL;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = value;
	new->type = num;
	new->next = NULL;
	return (new);
}

static void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*tmp = NULL;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	sort_redirections(t_cmd *cmd_current, t_token **tmp)
{
	t_redir *new = NULL;

	new = new_redir((*tmp)->next->value, (*tmp)->type);
	redir_add_back(&cmd_current->redirections, new);
	*tmp = (*tmp)->next;
}
