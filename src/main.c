/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/08/26 11:47:51 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void print_shell_envi(t_env *head)
// {
// 	t_env *tmp;

// 	tmp = head;
// 	while (head)
// 	{
// 		ft_printf("Key: %d\n", tmp->key);
// 		ft_printf("Value: %d\n", tmp->value);
// 		tmp = tmp->next;
// 	}
// }

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
// 		if (!cur->args)
// 			return ;
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

			// print_tokens(minishell.tokens);
			// print_cmd(minishell.cmdline);
			// print_cmd(minishell->cmdline);

// helper to take signal setting out of main to save lines.
int	run_signal(t_shell *shell, char *input)
{
	g_signal_status = 0;
	shell->exit = 130;
	free(input);
	return (1);
}

// helper to take running of the whole shell out of main to save lines.
void	run_shell(t_shell *minishell)
{
	minishell->exit = process(minishell, minishell->tokens);
	exe_cmdline(minishell);
	free_tokens(&minishell->tokens);
	free_cmd(&minishell->cmdline);
}

// simple main, declare our shell, bzero to set it to 0 then populate env.
// enter while loop and initiate signal handling.
// set prompt. input becomes user input.
// if we have no input or the input is exit, we break and quit the shell.
// if our signal handler detects SIGINT, we continue, resetting back at prompt.
// if input is present we add the input to history, then tokenize.
// if we have a valid set of tokens we finally run the shell, we process, expand
// and execute before freeing everything and returning back to the shell input.
// once we leave the main loop, free shell insures we have freed everything.
int	main(int argc, char **argv, char **envp)
{
	t_shell	minishell;
	char	*input;

	ft_bzero(&minishell, sizeof(t_shell));
	minishell.env = init_env(envp, NULL, NULL);
	while (minishell.status == 0)
	{
		init_signals(argc, argv);
		input = readline("/minishell$ ");
		if (!input && ft_printf("exit\n"))
			break ;
		if (g_signal_status == SIGINT && run_signal(&minishell, input))
			continue ;
		if (*input)
		{
			add_history(input);
			minishell.tokens = tokenize(input, &minishell);
			if (minishell.tokens)
				run_shell(&minishell);
		}
		free(input);
	}
	free_shell(&minishell);
	return (minishell.exit);
}
