/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:44:29 by jfox              #+#    #+#             */
/*   Updated: 2026/08/19 18:35:38 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// used to print error for the heredoc parsing in new_redir
static int hd_error(t_redir *new, char *value, int qstatus, int etype)
{
	if (etype == 1 && (!value)) //check error 1
	{
		ft_putstr_fd("minishell: null token passed to parsing HEREDOC\n", 2);
		free(new);
		return (1);
	}
	if (etype == 2 && (qstatus == -1)) // check error 2
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		free(new);
		return (1);
	}
	return (0);
}
// As with all structs, we have a helper to build it.
// However here we can fill it at the same time and we have passed information
// to this function.

// PK: Updated function to now parse heredoc.
// Checks if NULL, if Unclosed, and if Closed, Strips
static t_redir	*new_redir(char *value, t_token_type type)
{
	t_redir	*new;
	int		quote_status;

	new = ft_calloc(sizeof(t_redir), 1);
	if (!new)
		return (NULL);
	quote_status = 0;
	new->quoted = 0;
	if (type == HEREDOC)
	{
		if (hd_error(new, value, quote_status, 1)) //NULL token passed to HD
			return (NULL);
		quote_status = is_hd_quoted(value);
		if (hd_error(new, value, quote_status, 2))// ERROR: Unclosed Quote
			return (NULL);
		if(quote_status == 1) // quotes, and closed
		{
			new->quoted = 1;
			strip_quotes(value);
		}
	}
	new->file_name = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

// Very much the same as ENV_ADD_BACK. We move to the last node in the list and
// add the new struct there.
static void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

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
void	sort_redirections(t_shell *shell, t_cmd *cmd_current, t_token **tmp)
{
	t_redir	*new;

	if (!(*tmp)->next || (*tmp)->next->type != WORD)
	{
		ft_putstr_fd("minishell: syntax", 2);
		shell->exit = 2;
		return ;
	}
	new = new_redir((*tmp)->next->value, (*tmp)->type);
	if (!new)
		return ;
	redir_add_back(&cmd_current->redirections, new);
	*tmp = (*tmp)->next;
}
