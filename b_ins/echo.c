/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:06:50 by davda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:15:19 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_flag(char **cmds)
{
	int	i;
	int	j;

	i = 1;
	if (cmds && cmds[i] && cmds[i][0] == '-' && cmds[i][1] == 'n')
	{
		j = 2;
		while (cmds[i][j] == 'n')
			j++;
		if (!cmds[i][j])
			return (0);
		else
			return (1);
	}
	return (1);
}

static int	start_print(char **cmds)
{
	int	i;
	int	j;

	i = 1;
	while (cmds[i])
	{
		j = 1;
		if (cmds[i][0] == '-')
		{
			while (cmds[i][j] && cmds[i][j] == 'n')
				j++;
			if (!cmds[i][j])
				i++;
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}

static void	print_it(char **cmds, int flg, int i)
{
	if (flg == 1 || flg == 2)
	{
		while (cmds && cmds[i])
		{
			if (cmds && cmds[i])
				printf("%s", cmds[i++]);
			if (cmds && cmds[i])
				printf(" ");
		}
	}
	else if (flg == 0)
	{
		while (cmds && cmds[i])
		{
			if (cmds && cmds[i])
				printf("%s", cmds[i++]);
			if (cmds && cmds[i])
				printf(" ");
		}
	}
	if (flg == 1 || flg == 2)
		printf("\n");
}

void	echo(char **cmds, int rexit, t_shelgon *shelgon)
{
	int	i;
	int	flg;

	shelgon->status = 0;
	if (cmds && !cmds[1])
	{
		ft_putchar_fd('\n', 1);
		if (rexit)
			return ;
		free_all(shelgon, shelgon->exe, BTIN);
		exit (0);
	}
	else if (cmds && cmds[1][0] == '-' && cmds[2])
		flg = check_flag(cmds);
	else if ((cmds[1][0] == '-' && (!cmds[1][1] || cmds[1][1] == 'n'))
				&& !cmds[2])
		flg = -1;
	else
		flg = 1;
	i = start_print(cmds);
	print_it(cmds, flg, i);
	if (rexit)
		return ;
	free_all(shelgon, shelgon->exe, BTIN);
	exit (0);
}
