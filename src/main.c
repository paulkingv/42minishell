/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/07/13 16:04:19 by pking            ###   ########.fr       */
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
	(void)ac;
	(void)av;
	// (void)envp;

	// function to take envp to environmental workspace and run all tests, keeping main clean.
	// environment_checks(envp);
	init_env(envp);

	// show working directory as a test.
	// make this a function later to show current position at all times.
	//char cwd[BUFSIZ];
	//getcwd(cwd, sizeof(cwd));

	// UNCOMMENT THIS WHEN READY
	// t_token *tokens;
	// t_cmd *cmdline;
	// char *input;
	// while (1)
	// {
	// 	ft_printf("%s/", cwd);
	// 	input = readline("minishell$ ");
	// 	if (!input) // Ctrl + D (End of File)
	// 		break;
	// 	if (*input) //Only add non empty lines to history
	// 		add_history(input);

	// 	/* Start Processing the command here */
	// 	// TOKENIZE
	// 	tokens = tokenize(input);
	// 	// MAKE STRUCTS PER COMMAND
	// 	cmdline = parse(tokens);	// TODO: FOX
	// 	// EXECUTE TOKENS
	// 	exec_cmdline(cmdline, envp);
	// 	// testing: print_tokens(tokens);
	// 	//ft_printf("%s\n", line);
	// 	free(input);
	// 	free_tokens(tokens);		// TODO
	// 	free_cmdline(cmdline);		// TODO
	// }
	return (0);
}

