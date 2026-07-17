/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:44:29 by jfox              #+#    #+#             */
/*   Updated: 2026/07/17 12:37:08 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// As with all structs, we have a helper to build it.
// However here we can fill it at the same time and we have passed information to this function.
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

// Very much the same as ENV_ADD_BACK. We move to the last node in the list and
// add the new struct there.
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

// A simple helper to build new redirects as needed, and fill them with the info
// passed to it by sort_tokens.
void	sort_redirections(t_cmd *cmd_current, t_token **tmp)
{
	t_redir *new = NULL;

	new = new_redir((*tmp)->next->value, (*tmp)->type);
	redir_add_back(&cmd_current->redirections, new);
	*tmp = (*tmp)->next;
}
