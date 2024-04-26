/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:02:54 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/26 17:16:50 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset(t_shelgon *shell, char **cmds, int flg)
{
	int	i;
	t_env	*cur;
	t_env	*tmp;
	t_env	*head;

	i = 1;
	cur = shell->env;
	head = shell->env;
	tmp = shell->env;
	while (cmds[i])
	{
		while (tmp)
		{
			if (tmp && (ft_strcmp(tmp->vr, cmds[i]) == 0 || ft_strcmp(tmp->cpy, cmds[i]) == 0))
			{
				if (!tmp->next)
					cur = tmp;
				else if (!tmp->prev)
					shell->env = tmp->next;
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				free(tmp->cpy);
				if (tmp->vr)
					free(tmp->vr);
				free(tmp);
				tmp = cur;
			}
			tmp = tmp->next;
		}
		tmp = head;
		i++;
	}
	if (flg)
		return ;
	free_all(shell, shell->exe, BTIN);
	exit (0);
}
