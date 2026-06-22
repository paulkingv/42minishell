/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/06/21 19:30:51 by pking            ###   ########.fr       */
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

int main (void)
{
	// Kick off the Shell

	// Wait for arguments to come in, in a loop

	// Take arguments -> Parser

	// Return Parser arguments -> Executor

	// Return Executor result -> Shell
	t_token *tokens;
	char *line;
	while (1)
	{
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

