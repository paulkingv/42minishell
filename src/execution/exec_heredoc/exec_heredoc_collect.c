/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_collect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:24:04 by pking             #+#    #+#             */
/*   Updated: 2026/08/30 19:19:18 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// DESCRIPTION //
// Reads every HD in pipeline before any fork.
// STDIN is duplicated first, HD's SIGINT handler closes it to break out
// of readline, and in the parent, the fd has to be put back afterwards

int	collect_heredocs(t_shell *shell)
{
	t_cmd	*cmd;
	int		saved_in;
	int		status;

	saved_in = dup(STDIN_FILENO);
	status = 0;
	cmd = shell->cmdline;
	while (cmd && status == 0)
	{
		if (cmd->redirections)
			status = read_heredocs(cmd->redirections, shell);
		cmd = cmd->next;
	}
	if (saved_in > 0)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	return (status);
}

//Closes each command's redirection's heredoc fd if exist
static void	close_cmd_heredocs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC && redir ->heredoc_fd > 2)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -2;
		}
		redir = redir->next;
	}
}

// Used to close FD in parent after forking all children.
void	close_heredocs(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmdline;
	while (cmd)
	{
		close_cmd_heredocs(cmd->redirections);
		cmd = cmd->next;
	}
}

// Special error case: HD cant be read
void	heredoc_abort(t_shell *shell)
{
	close_heredocs(shell);
	reset_signals();
	if (g_signal_status == SIGINT)
		shell->exit = 130;
	else
		shell->exit = 1;
	g_signal_status = 0;
}
