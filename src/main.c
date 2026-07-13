/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/07/13 11:50:55 by jfox             ###   ########.fr       */
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

static void print_cmd(t_cmd *head)
{
	t_cmd	*cur = NULL;
	int		i;

	cur = head;
	i = 0;
	while (cur)
	{
		while (cur->args[i])
		{
			printf("arg[%d]: %s\n", i, cur->args[i]);
			i++;
		}
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

	// function to take envp to environmental workspace and run all tests, keeping main clean.
	environment_checks(envp);

	// show working directory as a test.
	// make this a function later to show current position at all times.
	char cwd[BUFSIZ];
	getcwd(cwd, sizeof(cwd));

	// PAUL WORKED DOWN HERE
	// int cmd_count;
	t_token *tokens;
	t_cmd *cmdline;
	char *input;
	while (1)
	{
		ft_printf("%s/", cwd);
		input = readline("minishell$ ");
		if (!input) // Ctrl + D (End of File)
			break;
		if (*input) //Only add non empty lines to history
			add_history(input);

		// /* Start Processing the command here */
		// // TOKENIZE
		tokens = tokenize(input);
		// // MAKE STRUCTS PER COMMAND
		cmdline = parse(tokens);	// TODO: FOX
		// // EXECUTE TOKENS
		// exec_cmdline(cmdline);	// TODO: PAUL
		print_tokens(tokens);
		print_cmd(cmdline);
		// //ft_printf("%s\n", line);
		// free(input);
		free_tokens(&tokens);		// TODO
		free_cmd(&cmdline);		// TODO
	}
	return (0);
}

