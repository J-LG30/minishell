/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:14:10 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/26 17:15:21 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(t_shelgon *shelgon, t_branch *cmds, t_exegg *exe)
{
	char	**full_cmd;
	int		status;
	int		i;

	i = 0;
	status = 0;
	full_cmd = cmds->full_cmd;
	while (full_cmd[i])
		i++;
	if (i > 2)
	{	
		ft_putstr_fd(ANGRY, 2);
		ft_putendl_fd(": exit: too many arguments", 2);
		shelgon->status = 1;
		return ;
	}
	i = 0;
	while(full_cmd[1] && full_cmd[1][i])
	{
		if (!ft_isdigit(full_cmd[1][i]))
		{
			ft_putendl_fd("exit (¬_¬)ﾉ", 2);
			ft_putstr_fd(ANGRY, 2);
			ft_putstr_fd(": exit: ", 2);
			ft_putstr_fd(full_cmd[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			status = 2;
			//break ;
		}
		i++;
	}
	if (status != 2)
	{		
		if (!full_cmd[1])
			status = shelgon->status;
		else
		{
			status = ft_atoi(full_cmd[1]);
			if (status < 0)
				status += 256;
		}
		ft_putendl_fd("exit (¬_¬)ﾉ", 2);
	}
	//printf("Status: %i\n", status);
	free_all(shelgon, shelgon->exe, BTIN);
	exit(status);
	//printf("did i not exit\n");
}