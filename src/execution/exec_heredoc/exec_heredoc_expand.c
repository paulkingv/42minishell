/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:34:24 by j.fox             #+#    #+#             */
/*   Updated: 2026/08/30 15:29:01 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_heredoc(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
	free(line);
	line = NULL;
	return ;
}

char	*expand_heredoc(t_shell *shell, char *line, char *string, int i)
{
	char	*tmp;

	string = ft_strdup("");
	if (!string)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1] == '$')
		{
			string = append_char(string, '$');
			i++;
		}
		else if (line[i] == '$')
		{
			tmp = expansion(shell, &line[i], &i);
			string = ap_string(string, tmp);
			free(tmp);
		}
		else
			string = append_char(string, line[i]);
		if (!string)
			return (NULL);
		i++;
	}
	return (string);
}
