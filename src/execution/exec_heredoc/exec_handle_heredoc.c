/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:17:04 by pking             #+#    #+#             */
/*   Updated: 2026/08/23 19:01:01 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *hd_expandline(char *line, t_env *env, int quoted)
{
	// MATT:
	/* here is where you put the function to expand
		 This function needs to check redir->quoted to know
		 if it should be expanded. 
	*/
	(void)env;
	(void)quoted;
	// if (!quoted)
	//	line = expand_variables(line, env);
	return (line);
}



// HD_NAME is used to gen a random* name for the HD
// Combines a static int val with PID (PID == prefix)
/*			NOTE: I had claude help me optimize for lines,
				so I reuse prefix as a container to become
				the string.
*/
static char *hd_name(void) //also needs to get the PID
{
	char			*ptr;
	char			filename[128];
	unsigned long	start_counter;
	int				fd;

	ptr = malloc(1);
	start_counter = (unsigned long)ptr;
	fd = -1;
	while (fd == -1)
	{
		filename = ft_itoa(start_counter)
		fd = open(filename, O_WRONLY | O_CREAT |O_TRUNC | O_EXCL, 0644);
		start_counter++;
	}

	return(filename); //not finished
}


static void	hd_loop(int fd, t_redir *redir, t_env *env)
{
	char *line;

	while (1) // CHANGE TO GLOBAL SIGNAL VALUE LATER
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("error line unterminated hd_loop\n", 2);
			break ; // line unterminated (error?)
		}
		if (ft_strcmp(line, redir->file_name) == 0)
		{
			free(line);
			break ;
		}
		line = hd_expandline(line, env, redir->quoted);
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
	}
}

int handle_heredoc(t_redir *redir, t_env *env) //returns FD
{
	int 	fd;
	// char 	*filename;

	// filename = hd_name();
	// if (!filename)
	// 	return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd < 0)
	{
		free(filename);
		return (-1);
	}
	hd_loop(fd, redir, env);
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (fd);
}
