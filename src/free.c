/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 11:47:01 by jfox              #+#    #+#             */
/*   Updated: 2026/07/15 15:36:43 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*current = NULL;
	t_token	*next = NULL;

	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_env(t_env **s_env)
{
	t_env	*current = NULL;
	t_env	*next = NULL;

	current = *s_env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_redirections(t_cmd *current)
{
	t_redir	*current_redir = NULL;
	t_redir	*next = NULL;

	current_redir = current->redirections;
	while (current_redir)
	{
		next = current_redir->next;
		free(current_redir->file_name);
		free(current_redir);
		current_redir = current_redir->next;
	}
}

void	free_cmd(t_cmd **cmdline)
{
	t_cmd	*current = NULL;
	t_cmd	*next = NULL;
	int		i;

	current = *cmdline;
	while (current)
	{
		i = 0;
		next = current->next;
		while (current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		if (current->redirections)
		{
			free_redirections(current);
		}
		free(current);
		current = next;
	}
}
