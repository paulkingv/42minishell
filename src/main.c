/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/07/23 15:13:31 by jfox             ###   ########.fr       */
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

		// print_tokens(minishell->tokens);
		// print_cmd(minishell->cmdline);

int	main(int argv, char **argc, char **envp) //added environment table
{
	t_shell	minishell;
	char	*input;

	(void)argv;
	(void)argc;
	ft_bzero(&minishell, sizeof(t_shell));
	minishell.env = init_env(envp);
	while (minishell.status == 0)
	{
		input = readline("/minishell$ ");
		if (!input && ft_printf("exit\n"))
			break ;
		if (*input)
		{
			add_history(input);
			minishell.tokens = tokenize(input);
			minishell.cmdline = parse(minishell.tokens);
			exe_cmdline(&minishell);
			free_tokens(&minishell.tokens);
			free_cmd(&minishell.cmdline);
		}
		free(input);
	}
	free_shell(&minishell);
	return (minishell.exit);
}
