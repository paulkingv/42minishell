/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:17:04 by pking             #+#    #+#             */
/*   Updated: 2026/08/30 19:03:17 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_loop_rl(int fd, t_redir *redir, t_shell *shell)
{
	char	*line;
	char	*expanded;

	while (g_signal_status != SIGINT)
	{
		line = hd_read_line(redir);
		if (!line)
			break ;
		if (ft_strcmp(line, redir->file_name) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		if (!redir->quoted)
		{
			expanded = expand_heredoc(shell, line, NULL, 0);
			free(line);
			line = expanded;
			if (!line)
				break ;
		}
		finish_heredoc(line, fd);
	}
}

static int	hd_loop(int fd, t_redir *redir, t_shell *shell)
{
	g_signal_status = 0;
	heredoc_signals();
	hd_loop_rl(fd, redir, shell);
	reset_signals();
	if (g_signal_status == SIGINT)
		return (-1);
	return (0);
}

// returns FD
int	handle_heredoc(t_redir *redir, t_shell *shell)
{
	int		fd;
	char	*filename;
	int		loop_error;

	fd = -1;
	filename = hd_name(&fd);
	if (!filename)
		return (-1);
	loop_error = hd_loop(fd, redir, shell);
	close(fd);
	if (loop_error != -1)
		fd = open(filename, O_RDONLY);
	else
		fd = -1;
	unlink(filename);
	free(filename);
	return (fd);
}
