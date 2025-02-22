/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:10:00 by jle-goff          #+#    #+#             */
/*   Updated: 2025/01/14 13:21:32 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern void	rl_replace_line(const char *, int);

void	child_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	prompt_handler(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT)
		g_sig = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_child_handler(void)
{
	struct sigaction	sa;
	struct sigaction	act;

	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &act, NULL);
}

void	set_prompt_handler(void)
{
	struct sigaction	sa;
	struct sigaction	act;

	sa.sa_handler = &prompt_handler;
	sa.sa_flags = SA_RESTART;
	act.sa_flags = SA_RESTART;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
}
