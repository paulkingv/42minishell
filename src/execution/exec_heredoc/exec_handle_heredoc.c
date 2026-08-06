/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:17:04 by pking             #+#    #+#             */
/*   Updated: 2026/08/03 00:50:00 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_heredoc_line(int fd, char *line,t_env *env)
{
	int line_len;

	line_len = (ft_strlen(line) + 1);
	write(fd, line, line_len);
}
char *hd_name(int PID) //also needs to get the PID
{
static int 	count;
char		*num;
char		*prefix;
char		*filename;

if(!(num = ft_itoa(count++)));
	return (NULL);
if (!(pid_char = ft_itoa(pid)))
	return (NULL);
prefix = ft_strjoin ("./heredoc_", pid_char);
filename = ft_strjoin(prefix, num);
free(prefix);
free(pid_str);
free(num);
return(filename);
}

// char	*read_heredoc(char *delim, int quoted)
// {
// 	char *line
// 	while (1)
// 	{

// 	}
// }


int handle_heredoc(t_redir *redir, t_env *env) //returns FD
{
	int 	fd;
	char 	*filename;
	char	*line;

	filename = hd_name(getpid());

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	unlink(filename);
	free(filename);
	// dup2(fd, STDIN_FILENO);
	if(fd < 0)
		return (-1);
	while(1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->delimiter) == 0) //delim detect
		{
			free(line);
			break ;
		}
		if (!quoted)
			line = expand_variables(line, env);
		write_heredoc_line(fd, line, env);
		free(line);
	}
	close(fd);

	

}

