/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 07:35:34 by pking             #+#    #+#             */
/*   Updated: 2026/08/28 07:43:58 by pking            ###   ########.fr       */
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