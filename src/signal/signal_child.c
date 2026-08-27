/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 07:27:58 by pking             #+#    #+#             */
/*   Updated: 2026/08/27 04:59:05 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sigint_heredoc(int sig)
{
	(void)sig;
	g_signal_status = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc);
}

void default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

