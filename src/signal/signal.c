/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 03:23:35 by pking             #+#    #+#             */
/*   Updated: 2026/08/13 00:19:20 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* FUNCTIONS FOR HANDLING SIGNALS*/
/*
* Signals are Ctrl + D, C, /
* <signal.h> gives us access to defined structs and functs
* 	and MACROS
* 
*
*/

volatile sig_atomic_t g_signal_status = 0;

static void sig_handler_prompt(int sig)
{
	(void)sig;
	if (rl_line_buffer && *rl_line_buffer)
		add_history(rl_line_buffer);
	write(1, '\n', 1);
	rl_on-new_line():
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_status = SIGINT;
}

static void sigint_heredoc(int sig)
{
	(void);
	g_interrupt_signal = SIGINT;
	close(STDIN_FILENO);
}

void init_signals(void)
{
	struct sigaction	sa; // required to set up the struct to use

	ft_bzero(&sa, sizeof(sa)); // make sure no random data
	sa.sa_handler = handle_sigint; // setting the function as reaction
	sigaction(SIGINT, &sa, NULL); // setting up the signal response. (When SIGINT, use sa)
	signal(SIGQUIT, SIG_IGN); // actually send signal to handler
}

void signals_heredoc(void)
{
	signal(SIGINT, heredoc_sigint);
}

void	reset_signals;
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
}


