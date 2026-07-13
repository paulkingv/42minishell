/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 17:04:19 by jfox              #+#    #+#             */
/*   Updated: 2026/07/13 11:48:35 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new = NULL;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **head, t_env *new)
{
	t_env	*tmp = NULL;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

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

char	*get_env(t_env *s_env, char	*key)
{
	t_env	*tmp;
	int		i;

	//consider what you're looking for, key length or similar evn names can causes issues here
	tmp = s_env;
	i = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, i) != 0)
			tmp = tmp->next;
		else
			return(tmp->value);
	}
	return (NULL);
}

t_env	*find_env(t_env *s_env, char *key)
{
	t_env	*tmp;
	int		i;

	//consider what you're looking for, key length or similar evn names can causes issues here
	tmp = s_env;
	i = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, i) != 0)
			tmp = tmp->next;
		else
			return(tmp);
	}
	return (NULL);
}

t_env	*edit_env(t_env *s_env, char *key, char *new)
{
	t_env	*tmp;

	// check for variables that you want to change not existing.
	tmp = find_env(s_env, key);
	if (!tmp)
		return(NULL);
	free(tmp->value);
	tmp->value = ft_strdup(new);
	return(tmp);
}

void	set_env(t_env **s_env, char *key, char *value)
{
	t_env	*tmp = NULL;
	t_env	*new = NULL;

	tmp = *s_env;
	if (find_env(tmp, key))
		edit_env(tmp, key, value);
	else
	{
		new = new_env(key, value);
		env_add_back(s_env, new);
	}
}

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

// test function for testing all above environmental functions.
void	environment_checks(char **envp)
{
	// Printing ENV as test ⬇️ comment this out for function below to work!
	// while(*envp)
	// {
	// 	ft_printf("%s\n", *envp);
	// 	envp++;
	// }
	// ft_printf("\n");

	// initialize the envp table with a function. do this once and store the information.
	// everytime we need to reference s_env we need to make a tmp struct!!
	t_env	*s_env = NULL;
	s_env = init_env(envp);
	// printf("DEBUG: %p\n", s_env);
	// printf("------------------------\n");

	// // attempt to print everything we have built in the lists as a test.
	t_env	*tmp = NULL;
	// tmp = s_env;
	// while (tmp)
	// {
	// 	printf("key:   %s\n", tmp->key);
	// 	printf("value: %s\n", tmp->value);
	// 	printf("------------------------\n");
	// 	tmp = tmp->next;
	// }
	// printf("DEBUG: %p\n", tmp);

	// // test returning a node from env linked list and the string value of the node
	// tmp = s_env;
	// tmp = find_env(tmp, "USER");
	// if (!tmp)
	// 	printf("node not found\n");
	// else
	// 	printf("Value exists: %p\n", tmp);
	// char *test = get_env(tmp, "USER");
	// if (!test)
	// 	printf("Key not found\n");
	// else
	// 	printf("User = %s\n", test);

	// printf("------------------------\n");

	// // test returning a second node from env linked list to check its a different value
	// tmp = s_env;
	// tmp = find_env(tmp, "PATH");
	// if (!tmp)
	// 	printf("node not found\n");
	// else
	// 	printf("Value exists: %p\n", tmp);
	// test = get_env(tmp, "PATH");
	// if (!test)
	// 	printf("Key not found\n");
	// else
	// 	printf("Path exists: %s\n", test);

	// printf("------------------------\n");

	// // test editing an env variable.
	// // assume parsing and tokenizer have given us the 'USER = bob' as tokens to use.
	// tmp = s_env;
	// tmp = edit_env(tmp, "USER", "bob");
	// test = get_env(s_env, "USER");
	// if (!test)
	// 	printf("Key not found\n");
	// else
	// 	printf("User = %s\n", test);

	// // check address of the new env variable;
	// tmp = find_env(s_env, "USER");
	// if (!tmp)
	// 	printf("node not found\n");
	// else
	// 	printf("Value exists: %p\n", tmp);

	// printf("------------------------\n");

	// check adding new environmental variables.
	// create an if, so we either edit the variable or add a new one.
	// assume that key and value have been determined already.
	tmp = s_env;
	set_env(&tmp, "USER", "JOE");
	set_env(&tmp, "NEW_VAL", "TEST");
	set_env(&tmp, "NEW_VAL_NEXT", "TEST_AGAIN");

	// // reprint everything to see updates
	// tmp = s_env;
	// while (tmp)
	// {
	// 	printf("key:   %s\n", tmp->key);
	// 	printf("value: %s\n", tmp->value);
	// 	printf("------------------------\n");
	// 	tmp = tmp->next;
	// }

	// now we just need to be able to remove variables!
	// THIS SHOULD PRINT AN EMPTY LIST!
	unset_env(&s_env, "SYSTEMD_EXEC_PID");
	unset_env(&s_env, "SSH_AUTH_SOCK");
	unset_env(&s_env, "SESSION_MANAGER");
	unset_env(&s_env, "SSH_AGENT_PID");
	unset_env(&s_env, "GNOME_TERMINAL_SCREEN");
	unset_env(&s_env, "XDG_CURRENT_DESKTOP");
	unset_env(&s_env, "LANG");
	unset_env(&s_env, "GPG_AGENT_INFO");
	unset_env(&s_env, "DESKTOP_SESSION");
	unset_env(&s_env, "QT_IM_MODULE");
	unset_env(&s_env, "XDG_MENU_PREFIX");
	unset_env(&s_env, "XDG_SESSION_PAT");
	unset_env(&s_env, "NIX_PROFILES");
	unset_env(&s_env, "NIX_REMOTE");
	unset_env(&s_env, "DBUS_SESSION_BUS_ADDRESS");
	unset_env(&s_env, "DOCKER_HOST");
	unset_env(&s_env, "GTK_MODULES");
	unset_env(&s_env, "XDG_DATA_DIRS");
	unset_env(&s_env, "GTK_IM_MODULE");
	unset_env(&s_env, "__ETC_PROFILE_NIX_SOURCED");
	unset_env(&s_env, "USER");
	unset_env(&s_env, "XDG_SESSION_DESKTOP");
	unset_env(&s_env, "XDG_CONFIG_DIRS");
	unset_env(&s_env, "QT_ACCESSIBILITY");
	unset_env(&s_env, "GNOME_DESKTOP_SESSION_ID");
	unset_env(&s_env, "KRB5CCNAME");
	unset_env(&s_env, "LOGNAME");
	unset_env(&s_env, "XDG_SEAT_PATH");
	unset_env(&s_env, "GNOME_TERMINAL_SERVICE");
	unset_env(&s_env, "HOME");
	unset_env(&s_env, "PATH");
	unset_env(&s_env, "XDG_RUNTIME_DIR");
	unset_env(&s_env, "XMODIFIERS");
	unset_env(&s_env, "SHELL");
	unset_env(&s_env, "DBUS_STARTER_BUS_TYPE");
	unset_env(&s_env, "XDG_SESSION_TYPE");
	unset_env(&s_env, "NIX_SSL_CERT_FILE");
	unset_env(&s_env, "VTE_VERSION");
	unset_env(&s_env, "COLORTERM");
	unset_env(&s_env, "XAUTHORITY");
	unset_env(&s_env, "PWD");
	unset_env(&s_env, "DBUS_STARTER_ADDRESS");
	unset_env(&s_env, "DISPLAY");
	unset_env(&s_env, "TERM");
	unset_env(&s_env, "GDMSESSION");
	unset_env(&s_env, "XDG_SESSION_CLASS");
	unset_env(&s_env, "SHLVL");
	unset_env(&s_env, "OLDPWD");
	unset_env(&s_env, "FT_HOOK_NAME");
	unset_env(&s_env, "FT_HOOK_PATHNAME");
	unset_env(&s_env, "XDG_GREETER_DATA_DIR");
	unset_env(&s_env, "LIBVIRT_DEFAULT_URI");
	unset_env(&s_env, "LS_COLORS");
	unset_env(&s_env, "_");
	unset_env(&s_env, "NEW_VAL");
	unset_env(&s_env, "NEW_VAL_NEXT");

	printf("------------------------\n");

	// print to check remove
	tmp = s_env;
	while (tmp)
	{
		printf("key:   %s\n", tmp->key);
		printf("value: %s\n", tmp->value);
		printf("------------------------\n");
		tmp = tmp->next;
	}

	printf("------------------------\n");

	// tmp = s_enev;
	set_env(&s_env, "USER", "Matt");
	set_env(&s_env, "42", "LETS GO!");

	// print to check remove
	tmp = s_env;
	while (tmp)
	{
		printf("key:   %s\n", tmp->key);
		printf("value: %s\n", tmp->value);
		printf("------------------------\n");
		tmp = tmp->next;
	}

	//test to free everything
	free_env(&s_env);
}
