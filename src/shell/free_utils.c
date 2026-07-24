/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 11:47:01 by jfox              #+#    #+#             */
/*   Updated: 2026/07/24 11:20:10 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	if (!current)
		return ;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	free_env(t_env **s_env)
{
	t_env	*current;
	t_env	*next;

	current = *s_env;
	if (!current)
		return ;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*s_env = NULL;
}

static void	free_redirections(t_cmd *current)
{
	t_redir	*current_redir;
	t_redir	*next;

	current_redir = current->redirections;
	if (!current_redir)
		return ;
	while (current_redir)
	{
		next = current_redir->next;
		free(current_redir);
		current_redir = next;
	}
	current->redirections = NULL;
}

void	free_cmd(t_cmd **cmdline)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = *cmdline;
	if (!current)
		return ;
	while (current)
	{
		i = 0;
		next = current->next;
		while (current->args && current->args[i])
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
	*cmdline = NULL;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
