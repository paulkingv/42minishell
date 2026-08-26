/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:17:04 by pking             #+#    #+#             */
/*   Updated: 2026/08/26 07:02:23 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *hd_gen(char *ptr, unsigned long *memaddr, int *fd, char *filename)
{
	ptr = ft_ltoa(*memaddr);
	if (!ptr)
		return(NULL);
	filename = ft_strjoin("./heredoc_", ptr);
	free(ptr);
	if (!filename)
		return (NULL);
	*fd = open(filename, O_WRONLY | O_CREAT |O_TRUNC | O_EXCL, 0644);
	if (*fd >= 0)
	{
		close(*fd);
		return (filename);
	}
	free(filename);
	(*memaddr)++;
	return (NULL);
}

// HD_NAME is used to gen a random* name for the HD
// Combines a static int val with pointer value
// This was changed to generate value from memory space
static char *hd_name(void) 
{
	char			*ptr;
	char			*filename;
	unsigned long	memaddr;
	int				fd;

	ptr = malloc(1);
	if (!ptr)
		return (NULL);
	fd = -1;
	memaddr = (unsigned long)ptr;
	free(ptr);
	while (fd == -1)
		filename = hd_gen(ptr, &memaddr, &fd, filename);
	return (filename);
}


static int	hd_loop(int fd, t_redir *redir, t_env *env)
{
	char *line;

	(void)*env;
	g_signal_status = 0;
	heredoc_signals();
	while (g_signal_status != SIGINT)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal_status != SIGINT)
				ft_putstr_fd("warning: heredoc delimited by EOF\n", 2);
			break ; // line unterminated 
		}
		if (ft_strcmp(line, redir->file_name) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	free(line);
	reset_signals();
	if (g_signal_status == SIGINT)
		return (-1);
	return (0);
}

int handle_heredoc(t_redir *redir, t_env *env) //returns FD
{
	int 	fd;
	char 	*filename;
	int		loop_error;

	filename = hd_name();
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT |O_TRUNC, 0644);
	if (fd < 0)
	{
		free(filename);
		return (-1);
	}
	loop_error = hd_loop(fd, redir, env);
	close(fd);
	if (loop_error != -1)
		fd = open(filename, O_RDONLY);
	else
		fd = -1;
	unlink(filename);
	free(filename);
	return (fd);
}
