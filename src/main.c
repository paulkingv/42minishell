/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/06/24 18:33:03 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_tokens(t_token *head)
{
    t_token *cur;

    cur = head;
    while (cur)
    {
        printf("type: %d | value: '%s'\n", cur->type, cur->value);
        cur = cur->next;
    }
}

int main (int ac, char **av, char **envp) //added environment table
{
	/* Kick off the Shell
	Wait for arguments to come in, in a loop
	Take arguments -> Tokenizer->Parser
	Return Parser arguments -> Executor
	Return Executor result -> Shell
	*/

	(void)ac;
	(void)av;
	// (void)envp;

	// Printing ENV as test ⬇️ comment this out for function below to work!
	// while(*envp)
	// {
	// 	ft_printf("%s\n", *envp);
	// 	envp++;
	// }
	// ft_printf("\n");

	// initialize the envp table with a function. do this once and store the information.
	// everytime we need to reference s_env we need to make a tmp struct!!
	t_env	*s_env = init_env(envp);
	// printf("DEBUG: %p\n", s_env);
	// printf("------------------------\n");

	// attempt to print everything we have built in the lists as a test.
	t_env	*tmp = s_env;
	while (tmp)
	{
		printf("key:   %s\n", tmp->key);
		printf("value: %s\n", tmp->value);
		printf("------------------------\n");
		tmp = tmp->next;
	}
	// printf("DEBUG: %p\n", tmp);

	//test getting an environment variable.
	tmp = s_env;
	char *test = get_env(tmp, "USER");
	if (!test)
		printf("Key not found\n");
	else
		printf("%s\n", test);

	// show working directory as a test.
	// make this a function later to show current position at all times.
	char cwd[BUFSIZ];
	getcwd(cwd, sizeof(cwd));

	// PAUL WORKED DOWN HERE
	t_token *tokens;
	char *line;
	while (1)
	{
		ft_printf("%s/", cwd);
		line = readline("minishell$ ");
		if (!line) // Ctrl + D (End of File)
			break;
		if (*line) //Only add non empty lines to history
			add_history(line);

		//process the command here
		tokens = tokenize(line);
		print_tokens(tokens);

		//ft_printf("%s\n", line);
		free(line);
	}
	return (0);
}

