/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:38:11 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 13:59:17 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// As with all structs, a handle to create the node for a chained list.
// Here we also pass information so we fill the struct while we initialize it.
t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

// A simply string compare helper to check if the current environment variable
// is the one we are looking for, it returns a pointer to the desired variable.
t_env	*find_env(t_env *s_env, char *key)
{
	t_env	*tmp;

	tmp = s_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// Similar to above however this function returns the string of the Value at
// the desired environment node.
char	*get_env(t_env *s_env, char	*key)
{
	t_env	*tmp;

	tmp = find_env(s_env, key);
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

// pull the setting of PWD and OLDPWD into a helper to clean up init env.
void	setpwd(t_env **head)
{
	char	*value;

	value = getcwd(NULL, 0);
	if (value)
	{
		set_env(head, "PWD", value);
		set_env(head, "OLDPWD", NULL);
		free(value);
	}
	return ;
}

// a helper to find the key and value of the environment while initialisng
// our shells environment.
void	get_key_value(t_shell *shell, char **envp)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while ((*envp)[i] && (*envp)[i] != '=')
		i += 1;
	shell->key = ft_substr((*envp), x, i);
	i += 1;
	x = i;
	while ((*envp)[i] != '\0')
		i += 1;
	shell->value = ft_substr((*envp), x, i);
	return ;
}
