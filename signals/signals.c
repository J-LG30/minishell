/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:10:00 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/17 15:34:34 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	sig_handler(int sig)
// {
// 	if (sig == SIGINT && g_sig == IN_CHILD)
// 	{
// 		write(1, "in do nothing handler\n", 23);
// 		// rl_replace_line("", 1);
// 		rl_on_new_line();
// 		g_sig = 0;
// 	}
// 	else if (sig == SIGINT)
// 	{
// 		// ft_putnbr_fd(getpid(), 1);
// 		write(1, "in sig handler\n", 16);
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

void	child_handler(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
}

void	prompt_handler(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_child_handler()
{
	struct sigaction	sa;
	
	sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

void	set_prompt_handler()
{
	struct sigaction	sa;
	struct sigaction	act;
	
	sa.sa_handler = &prompt_handler;
	sa.sa_flags = SA_RESTART;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &act, NULL);
}