/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:39 by pking             #+#    #+#             */
/*   Updated: 2026/07/22 02:38:50 by pking            ###   ########.fr       */
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
		// print_tokens(minishell->tokens);
		// print_cmd(minishell->cmdline);

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
	t_shell	*minishell = NULL;
	char	*input;
	int		sig_exit;

	(void)argv;
	(void)argc;
	minishell = shell_init(envp);
	while (minishell->status == 1)
	{
		//ft_printf("%s/", ft_path(minishell));
		input = readline("minishell$ ");
		if (!input) // Ctrl + D (End of File)
			break;
		if (*input) //Only add non empty lines to history
			add_history(input);
		minishell->tokens = tokenize(input);
		minishell->cmdline = parse(minishell->tokens);
		exe_cmdline(minishell); // WORK REQUIRED!!!
		free_tokens(&minishell->tokens);
		free_cmd(&minishell->cmdline);
	}
	sig_exit = minishell->exit;
	free_env(&minishell->env);
	free_shell(minishell);
	return (sig_exit);
}


