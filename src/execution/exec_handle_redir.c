/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:49:09 by pking             #+#    #+#             */
/*   Updated: 2026/08/17 12:37:25 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CC created this function so that we scan the cmdline's redirs for HD
// in main.
int read_heredocs(t_redir *redir, t_env *env)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			redir->heredoc_fd = handle_heredoc(redir, env);
			if (redir->heredoc_fd == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
// This function is used in tandem with handle_redirects() in order to
// open/create a file to write to or read from.
//		CC told me to remove HD case
int	open_redir_file(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
		fd = open(redir->file_name, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	return (fd);
}

// CC says this should work
int	handle_redirects(t_redir *redir, t_env *env, t_shell *shell)
{
	int	fd;

	(void)*env; // have to change this later for the expansion
	fd = 0;
	while (redir)
	{

		if (redir->type == HEREDOC) // essential: do this in loop to read multiple HDs
		{
			fd = redir->heredoc_fd;
			safe_dup2(fd, STDIN_FILENO);
		}
		else
		{
			fd = open_redir_file(redir);
			if (fd == -1)
			{
				perror(redir->file_name);
				free_shell(shell);
				exit(1);
			}
			if (redir->type == REDIR_IN)
				safe_dup2(fd, 0); //dup2(fd, targetfd)
			else if (redir->type == REDIR_OUT || redir->type == APPEND)
				safe_dup2(fd, 1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
