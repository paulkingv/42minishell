/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:49:05 by jfox              #+#    #+#             */
/*   Updated: 2025/12/30 18:04:22 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	lenx;

	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	lenx = (len1 + ft_strlen(s2));
	s3 = (char *)ft_calloc((lenx + 1), sizeof(char));
	if (!s3)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(s3, s1, (len1 + 1));
		free(s1);
	}
	ft_strlcpy(&s3[len1], s2, ft_strlen(s2) + 1);
	return (s3);
}

static char	*build_line(int fd, char *stash, int *goodread)
{
	char	*unchecked_line;
	char	*temp;

	unchecked_line = stash;
	temp = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp)
		return (NULL);
	*goodread = 1;
	while (!ft_strchr(unchecked_line, '\n') && *goodread != 0)
	{
		*goodread = read(fd, temp, BUFFER_SIZE);
		if (*goodread == -1)
		{
			free(unchecked_line);
			free(temp);
			return (NULL);
		}
		temp[*goodread] = '\0';
		unchecked_line = ft_strjoin_gnl(unchecked_line, temp);
	}
	free(temp);
	return (unchecked_line);
}

static char	*check_line(char **stash)
{
	char	*checked_line;
	char	*tmp;
	int		len;

	if (*stash == NULL)
		return (NULL);
	len = 0;
	tmp = *stash;
	while (tmp[len] != '\n' && tmp[len])
		len++;
	if (tmp[len] == '\n')
		len++;
	checked_line = ft_substr(*stash, 0, len);
	if (!checked_line)
		return (NULL);
	tmp = ft_substr(*stash, len, ft_strlen(*stash));
	free(*stash);
	*stash = tmp;
	return (checked_line);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*newline;
	int			goodread;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
	{
		if (stash[fd])
			free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = build_line(fd, stash[fd], &goodread);
	newline = check_line(&stash[fd]);
	if ((newline == NULL || *newline == '\0'))
	{
		free(newline);
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	return (newline);
}
