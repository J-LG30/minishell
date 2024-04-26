/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:02:54 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/26 17:30:00 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strrem(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (!str2[i] && (ft_strlen(str1) > ft_strlen(str2)) && str1[i] == '=')
		return (0);
	return (str1[i] - str2[i]);
}

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
			if (tmp && (ft_strrem(tmp->cpy, cmds[i]) == 0))
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
				if (tmp->vr && ft_strcmp(tmp->cpy, tmp->vr) == 0)
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
	exit (1);
}
