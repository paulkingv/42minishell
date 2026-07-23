/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 00:51:05 by pking             #+#    #+#             */
/*   Updated: 2026/07/21 17:20:01 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *join_path_cmd (char *path_i, char*cmd)
{
	char	*s3;
	size_t	len1;
	size_t	len2;
	size_t	lenx;

	if (!path_i || !cmd)
		return (NULL);
	len1 = ft_strlen(path_i);
	len2 = ft_strlen(cmd);
	lenx = (len1 + len2 + 2);
	s3 = (char *)ft_calloc((lenx + 2), sizeof(char));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, path_i, (len1 + 1));
	s3[len1] = '/';
	s3[len1 + 1] = '\0';
	ft_strlcat(s3, cmd, (lenx + 1));
	return (s3);
}

static int count_colons(char *path_value)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (path_value[i])
	{
		if (path_value[i] == ':')
			count++;
		i++;
	}
	return (count);
}

// 1. GO through ENVP Linked List in order to FIND PATH VARIABLE
static char *find_path(t_shell *shell)
{
	t_env *tmp = NULL;

	tmp = shell->env;
	if (!tmp)
		return (NULL);
	while (tmp && (ft_strncmp(tmp->key, "PATH", 5) != 0)) //while the key inside tmp does not equal "PATH"
		tmp = tmp->next;
	if (tmp)
		return (tmp->value);
	return (NULL);
}

// 2. We have the path. Lets make the split and access function
// NOTE ⬇️ This leaks [path_cmd needs to be freed]. Free one layer above
static char *split_and_try_access(char *path_value, char *cmd)
{
	char **paths;
	int paths_count;
	char *path_cmd;
	int i;

	i = 0;
	paths_count = count_colons(path_value);
	paths = ft_split(path_value, ':');
	while (i < paths_count + 1) // while i is less than our colon amount + 1
	{
			path_cmd = join_path_cmd(paths[i], cmd);
			if (access(path_cmd, X_OK) == 0)
			{
				free_array(paths);
				return (path_cmd);
			}
			free(path_cmd);
			i++;
	}
	free_array(paths);
	return (NULL);
}

//Meat function. Returns the string of the first possible exec path

char *exec_get_valid_path(t_shell *shell, char *cmd)// shell and argv0
{
	char	*path_value;
	char	*valid_path_cmd;

	path_value = find_path(shell);
	if (path_value)
	{
		if (ft_strchr(cmd, '/'))
		{
			if (access(cmd, X_OK) == 0)
				return (cmd);
			else
				return (NULL);
		}
		valid_path_cmd = split_and_try_access(path_value, cmd);
			if (valid_path_cmd)
				return (valid_path_cmd);
			else
				return (NULL);
	}
	else
		return (NULL);
}
