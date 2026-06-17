/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/06/17 16:40:20 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main (void)
{
	// Kick off the Shell

	// Wait for arguments to come in, in a loop

	// Take arguments -> Parser

	// Return Parser arguments -> Executor

	// Return Executor result -> Shell

	char *line;
	while (1)
	{
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

