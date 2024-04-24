/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:06:50 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/24 18:44:40 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_flag(char **cmds)
{
	int	i;
	int	j;
	int	res;

	i = 1;
	j = 1;
	res = 0;
	while (cmds[i][0] == '-')
	{
		while (cmds[i][j])
		{
			if (cmds[i][j] != 'n')
				res = 2;
			j++;
		}
		i++;
	}
	return (res);
}

static int	start_print(char **cmds, int flg)
{
	int	i;

	i = 1;
	if (flg == 2 || flg == -1)
		return (1);
	while (cmds[i][0] == '-')
		i++;
	return (i);
}

static void	print_it(char **cmds, int flg, int i)
{
	if (flg == 1 || flg == 2)
		while (cmds[i])
		{
			printf("%s", cmds[i++]);
			if (cmds[i])
				printf(" ");
		}
	else if (flg == 0)
		while (cmds[i])
		{
			if (cmds[i])
				printf("%s", cmds[i++]);
			if (cmds[i])
				printf(" ");
		}
	if (flg == 1 || flg == 2)
		printf("\n");
}

static int	check_args(char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i] && cmds[i][0] == '-')
		i++;
	if (cmds[i])
		return (0);
	return (1);
}
//FIX SEGFAULT IF: echo -n -n test

void	echo(char **cmds, int rexit)
{
	int	i;
	int	flg;

	i = 0;
	if (!cmds[1])
		ft_putchar_fd('\n', 2);
	if (check_args(cmds))
	{
		if (rexit)
			return ;
		exit (0);
	}
	if (cmds[1][0] == '-' && cmds[2])
		flg = check_flag(cmds);
	else if (cmds[1][0] == '-' && !cmds[2])
		flg = -1;
	else
		flg = 1;
	i = start_print(cmds, flg);
	print_it(cmds, flg, i);
	if (rexit)
		return ;
	exit (0);
}
