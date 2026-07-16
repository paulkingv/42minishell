/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:49:09 by pking             #+#    #+#             */
/*   Updated: 2026/07/16 02:57:13 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function is used in tandem with handle_redirects() in order to open/create a file to write to or read from.
int open_redir_file(t_redir *redir)
{
	int fd;

	if (redir->type == REDIR_IN)
		fd = open(redir->file_name, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)
	else if (redir->type == HEREDOC)
		return (-1);
	else
		return (-1);
	return (fd);
}

int handle_redirects(t_redir *redir)
{
	int fd;

	while (redir)
	{
		fd = open_redir_file(redir);
		if (fd == -1)
		{
			perror(redir->file_name);
			exit(1);
		}
		//dup2(fd, targetfd)
		if (redir->type == REDIR_IN)
			safe_dup2(fd, 0);
		if (redir->type == REDIR_OUT || redir->type == APPEND)
			safe_dup2(fd, 1);	
		close(fd);
		redir = redir->next;
	}
	return (fd);
}
