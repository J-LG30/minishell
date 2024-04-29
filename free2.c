/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:31:54 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/29 09:35:37 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	free_branch(t_branch *branch)
{
	t_branch	*cursor;
	int			i;

	if (!branch)
		return ;
	cursor = branch;
	while (branch)
	{
		free(branch->full_cmd);
		branch = branch->next;
		if (cursor)
			free(cursor);
		cursor = branch;
	}
	if (branch)
		free(branch);
}

void	free_exegg(t_exegg *exe)
{
	int	i;

	i = 0;
	if (!exe)
		return ;
	free_branch(exe->cmd);
	while (exe->cmdpath && exe->cmdpath[i])
	{
		free(exe->cmdpath[i]);
		i++;
	}
	free(exe->cmdpath);
	free(exe);
}
