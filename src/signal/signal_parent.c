/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 03:23:35 by pking             #+#    #+#             */
/*   Updated: 2026/08/29 16:52:22 by pking            ###   ########.fr       */
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

static void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_status = SIGINT;
}


void init_signals(int argc, char **argv)
{
	struct sigaction	sa; // required to set up the struct to use

	(void)argv;
	(void)argc;
	ft_bzero(&sa, sizeof(sa)); // make sure no random data
	sa.sa_handler = handle_sigint; // setting the function as reaction
	sigaction(SIGINT, &sa, NULL); // setting up the signal response. (When SIGINT, use sa)
	signal(SIGQUIT, SIG_IGN); // actually send signal to handler
}


void reset_signals(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
}

void parent_wait_signals(void)
{
	signal(SIGINT, SIG_IGN);
}
