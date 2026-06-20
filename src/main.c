/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/06/20 17:26:44 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac, char **av, char **envp) //added environment table
{
	// Kick off the Shell

	// Wait for arguments to come in, in a loop

	// Take arguments -> Parser

	// Return Parser arguments -> Executor

	// Return Executor result -> Shell

	// print environment table as a test
	(void)ac;
	(void)av;
	while(*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	ft_printf("\n");
	// show working directory as a test.
	// make this a function later to show current position at all times.
	char cwd[BUFSIZ];
	getcwd(cwd, sizeof(cwd));

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
		ft_printf("%s\n", line);
		free(line);
	}
	return (0);
}

