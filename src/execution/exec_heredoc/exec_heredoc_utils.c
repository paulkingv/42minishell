/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 07:35:34 by pking             #+#    #+#             */
/*   Updated: 2026/08/29 10:45:46 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*raw_readline(void)
{
	char	*line;
	char	c;
	int		n;
	int		got;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	got = 0;
	n = read(STDIN_FILENO, &c, 1);
	while (n > 0 && c != '\n')
	{
		got = 1;
		line = append_char(line, c);
		if (!line)
			return (NULL);
		n = read(STDIN_FILENO, &c, 1);
	}
	if (n <= 0 && !got)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*hd_read_line(t_redir *redir)
{
	char *line;

	if (isatty(STDIN_FILENO))
		line = readline("> ");
	else
		line = raw_readline();
	if (!line && g_signal_status != SIGINT)
	{
		ft_putstr_fd("minishell: warning: here-document delimited", 2);
		ft_putstr_fd(" by end of file (wanted `", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd("')\n", 2);
	}
	return (line);
}

//helper to read all heredocs
// will close fd if hd is interuppted partway through pipeline
static void close_pending_heredocs(t_cmd *cmd)
{
	t_redir *redir;
	
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
// reads all hds for every command of pipeline at beginning
// keeps concurrent HDs from corrupting 
int read_all_heredocs(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmdline;
	while (cmd)
	{
		if (cmd->redirections && read_heredocs(cmd->redirections, shell) == -1)
		{
			close_pending_heredocs(shell->cmdline);
			return (-1);
		}
		cmd = cmd->next;
	}
	return (0);
}