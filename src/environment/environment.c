/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 17:04:19 by jfox              #+#    #+#             */
/*   Updated: 2026/07/23 00:13:43 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PK: Changed "new" to "new_node" (new is a keyword & was getting flagged)
// 		[I did that in 3 functions. Now compiles w/o error. Delete this once read]

// A helper for set env, that actually edits the value.
t_env	*edit_env(t_env *s_env, char *key, char *new_node)
{
	t_env	*tmp;

	// check for variables that you want to change not existing.
	tmp = find_env(s_env, key);
	if (!tmp)
		return(NULL);
	free(tmp->value);
	tmp->value = ft_strdup(new_node);
	return(tmp);
}

// Change the value of an environment variable using find and a new string.
// This will be used by export when we do the built ins.
void	set_env(t_env **s_env, char *key, char *value)
{
	t_env	*tmp = NULL;
	t_env	*new_node = NULL;

	tmp = *s_env;
	if (find_env(tmp, key))
		edit_env(tmp, key, value);
	else
	{
		new_node = new_env(key, value);
		env_add_back(s_env, new_node);
	}
}

// Allows you to remove an environment variable by freeing the data sorted there
// Then we make the previous node point to the next node.
void	unset_env(t_env **head, char *key)
{
	t_env	*current = NULL;
	t_env	*prev = NULL;

	current = *head;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key)))
		{
			if(current == *head)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

// A simple function to add new data to a chained list.
// We first fill head if it doesnt exist. Then subsequent calls will move to the
// end of the chained list and place a node there.
void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*tmp = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

// Horrible function.
// To long, too many variables, no error handling or protections...
// Here we go through the string envp and break it into key and value.
// Cutting it using the = sign in the envp.
// See above for new_env and env_add back.
t_env	*init_env(char **envp)
{
	int		i;
	int		x;
	char	*key;
	char	*value;
	t_env	*head = NULL;
	t_env	*new = NULL;

	while (*envp)
	{
		i = 0;
		x = 0;
		while ((*envp)[i] && (*envp)[i] != '=')
			i++;
		key = ft_substr((*envp), x, i);
		i++;
		x = i;
		while ((*envp)[i] != '\0')
			i++;
		value = ft_substr((*envp), x, i);
		new = new_env(key, value);
		env_add_back(&head, new);
		free(key);
		free(value);
		envp++;
	}
	return (head);
}

// Notes on env and every single variable in the ENVP list.
//******ELLIOT COMMENT: env -i ./minishell to launch the project, you get an empty env var list (testing to see if we've hardcoded in certain env vars)
// 	All the possible current ENV variables when loading a stock shell.
// 	unset_env(&s_env, "SYSTEMD_EXEC_PID");
// 	unset_env(&s_env, "SSH_AUTH_SOCK");
// 	unset_env(&s_env, "SESSION_MANAGER");
// 	unset_env(&s_env, "SSH_AGENT_PID");
// 	unset_env(&s_env, "GNOME_TERMINAL_SCREEN");
// 	unset_env(&s_env, "XDG_CURRENT_DESKTOP");
// 	unset_env(&s_env, "LANG");
// 	unset_env(&s_env, "GPG_AGENT_INFO");
// 	unset_env(&s_env, "DESKTOP_SESSION");
// 	unset_env(&s_env, "QT_IM_MODULE");
// 	unset_env(&s_env, "XDG_MENU_PREFIX");
// 	unset_env(&s_env, "XDG_SESSION_PAT");
// 	unset_env(&s_env, "NIX_PROFILES");
// 	unset_env(&s_env, "NIX_REMOTE");
// 	unset_env(&s_env, "DBUS_SESSION_BUS_ADDRESS");
// 	unset_env(&s_env, "DOCKER_HOST");
// 	unset_env(&s_env, "GTK_MODULES");
// 	unset_env(&s_env, "XDG_DATA_DIRS");
// 	unset_env(&s_env, "GTK_IM_MODULE");
// 	unset_env(&s_env, "__ETC_PROFILE_NIX_SOURCED");
// 	unset_env(&s_env, "USER");
// 	unset_env(&s_env, "XDG_SESSION_DESKTOP");
// 	unset_env(&s_env, "XDG_CONFIG_DIRS");
// 	unset_env(&s_env, "QT_ACCESSIBILITY");
// 	unset_env(&s_env, "GNOME_DESKTOP_SESSION_ID");
// 	unset_env(&s_env, "KRB5CCNAME");
// 	unset_env(&s_env, "LOGNAME");
// 	unset_env(&s_env, "XDG_SEAT_PATH");
// 	unset_env(&s_env, "GNOME_TERMINAL_SERVICE");
// 	unset_env(&s_env, "HOME");
// 	unset_env(&s_env, "PATH");
// 	unset_env(&s_env, "XDG_RUNTIME_DIR");
// 	unset_env(&s_env, "XMODIFIERS");
// 	unset_env(&s_env, "SHELL");
// 	unset_env(&s_env, "DBUS_STARTER_BUS_TYPE");
// 	unset_env(&s_env, "XDG_SESSION_TYPE");
// 	unset_env(&s_env, "NIX_SSL_CERT_FILE");
// 	unset_env(&s_env, "VTE_VERSION");
// 	unset_env(&s_env, "COLORTERM");
// 	unset_env(&s_env, "XAUTHORITY");
// 	unset_env(&s_env, "PWD");
// 	unset_env(&s_env, "DBUS_STARTER_ADDRESS");
// 	unset_env(&s_env, "DISPLAY");
// 	unset_env(&s_env, "TERM");
// 	unset_env(&s_env, "GDMSESSION");
// 	unset_env(&s_env, "XDG_SESSION_CLASS");
// 	unset_env(&s_env, "SHLVL");
// 	unset_env(&s_env, "OLDPWD");
// 	unset_env(&s_env, "FT_HOOK_NAME");
// 	unset_env(&s_env, "FT_HOOK_PATHNAME");
// 	unset_env(&s_env, "XDG_GREETER_DATA_DIR");
// 	unset_env(&s_env, "LIBVIRT_DEFAULT_URI");
// 	unset_env(&s_env, "LS_COLORS");
// 	unset_env(&s_env, "_");
// 	unset_env(&s_env, "NEW_VAL");
// 	unset_env(&s_env, "NEW_VAL_NEXT");
