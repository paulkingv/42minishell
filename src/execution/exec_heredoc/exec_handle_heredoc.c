/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:17:04 by pking             #+#    #+#             */
/*   Updated: 2026/08/27 21:07:07 by pking            ###   ########.fr       */
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

// inside hd_loop, this is readline for hd; also checks if EOF or ^C
static void	hd_loop_rl(int fd, t_redir *redir) //, char *line
{
	char *line;

	while (g_signal_status != SIGINT)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal_status != SIGINT)
				ft_putstr_fd("warning: heredoc delimited by EOF\n", 2);
			break ; // line unterminated, ^C
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
}

static int	hd_loop(int fd, t_redir *redir, t_env *env)
{
	// char *line;

	// lines = NULL;
	(void)*env;
	g_signal_status = 0;
	heredoc_signals();
	hd_loop_rl(fd, redir); //, line
	// free(line);
	reset_signals();
	if (g_signal_status == SIGINT)
		return (-1);
	return (0);
}

//returns FD
int handle_heredoc(t_redir *redir, t_env *env)
{
	int 	fd;
	char 	*filename;
	int		loop_error;

	filename = hd_name();
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); //Write only, create if !exist, truncate to it, 0644 == perms
	if (fd < 0)
	{
		free(filename);
		return (-1);
	}
	loop_error = hd_loop(fd, redir, env); // run the readline loop
	close(fd);
	if (loop_error != -1)
		fd = open(filename, O_RDONLY);
	else
		fd = -1;
	unlink(filename);
	free(filename);
	return (fd);
}
