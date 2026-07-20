/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/07/20 14:51:39 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void print_tokens(t_token *head)
// {
//     t_token *cur;

//     cur = head;
//     while (cur)
//     {
//         printf("type: %d | value: '%s'\n", cur->type, cur->value);
//         cur = cur->next;
//     }
// }

// static void print_cmd(t_cmd *head)
// {
// 	t_cmd	*cur = NULL;
// 	t_redir *redir = NULL;
// 	int		i;
// 	int		x;

// 	cur = head;
// 	x = 1;
// 	while (cur)
// 	{
// 		i = 0;
// 		redir = cur->redirections;
// 		printf("Command %d: \n",x);
// 		while (cur->args[i])
// 		{
// 			printf("arg[%d]: %s\n", i, cur->args[i]);
// 			i++;
// 			if (redir)
// 			{
// 				while (redir)
// 				{
// 					printf("redirection: %d\n", redir->type);
// 					printf("File: %s\n", redir->file_name);
// 					redir = redir->next;
// 				}
// 			}
// 		}
// 		x++;
// 		cur = cur->next;
// 	}
// }

int main (int argv, char **argc, char **envp) //added environment table
{
	/* Kick off the Shell
	Wait for arguments to come in, in a loop
	Take arguments -> Tokenizer->Parser
	Return Parser arguments -> Executor
	Return Executor result -> Shell
	*/
	t_shell	*minishell = NULL;
	char	*input;
	int		sig_exit;

	(void)argv;
	(void)argc;
	minishell = shell_init(envp);
	while (1)
	{
		ft_printf("%s/", ft_path(minishell));
		input = readline("minishell$ ");
		if (!input) // Ctrl + D (End of File)
			break;
		if (*input) //Only add non empty lines to history
			add_history(input);
		/* Start Processing the command here */
		// TOKENIZE
		minishell->tokens = tokenize(input);
		// MAKE STRUCTS PER COMMAND
		minishell->cmdline = parse(minishell->tokens);
		// EXECUTE TOKENS
		exe_cmdline(minishell); // WORK REQUIRED!!!
		// print_tokens(minishell->tokens);
		// print_cmd(minishell->cmdline);
		free_tokens(&minishell->tokens);
		free_cmd(&minishell->cmdline);
	}
	sig_exit = minishell->exit;
	free_env(&minishell->env);
	free(minishell);
	ft_printf("exit\n");
	return (sig_exit);
}
