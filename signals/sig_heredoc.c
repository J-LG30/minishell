/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:32:40 by jle-goff          #+#    #+#             */
/*   Updated: 2025/01/14 12:34:40 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern void	rl_replace_line(const char *, int);

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		//g_sig = 1;
		write(1, "\n", 1);
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

void	set_heredoc_handler(void)
{
	struct sigaction	sa;
	struct sigaction	act;

	sa.sa_flags = 0;
	sa.sa_handler = &heredoc_handler;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
}
