/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:41:47 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/01 15:15:09 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_sort(char **copy)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	while (1)
	{
		flag = 0;
		i = 0;
		while (copy && copy[i])
		{
			if (copy && copy[i] && copy[i + 1] && ft_strcmp(copy[i], copy[i + 1]) >= 0)
			{
				flag = 1;
				tmp = copy[i];
				copy[i] = copy[i + 1];
				copy[i + 1] = tmp;
			}
			i++;
		}
		if (flag == 0)
			break ;
	}
}

char	**sort_exp(t_shelgon *shell, char **copy)
{
	t_env	*tmp;
	char	*var_tmp;
	int		i;

	tmp = shell->env;
	i = 0;
	copy = (char **)malloc(sizeof(char *) * (ms_lstsize(tmp) + 1));
	if (!copy)
		return (NULL);
	while (tmp)
	{
		copy[i] = tmp->cpy;
		tmp = tmp->next;
		i++;
	}
	copy[i] = NULL;
	print_sort(copy);
	return(copy);
}
