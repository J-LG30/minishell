/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:29:05 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/30 16:48:26 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ms_lstsize(t_env *lst)
{
	int		size;
	t_env	*cursor;

	if (lst == NULL)
		return (0);
	size = 0;
	cursor = lst;
	while (cursor != 0)
	{
		size++;
		cursor = cursor -> next;
	}
	return (size);
}

char	**sort_exp(t_shelgon *shell, char **copy)
{
	t_env	*tmp;
	char	*var_tmp;
	int		i;
	int		flag;

	tmp = shell->env;
	i = 0;
	copy = (char **)malloc(sizeof(char *) * (ms_lstsize(tmp) + 1));
	if (!copy)
		return (NULL);
	flag = 0;
	while (1)
	{
		flag = 0;
		while (tmp)
		{
			if (tmp->next && ft_strcmp(tmp->cpy, tmp->next->cpy) > 0)
			{
				flag = 1;
				var_tmp = tmp->cpy;
				copy[i] = var_tmp;
				var_tmp = tmp->next->cpy;
				i++;
				copy[i] = var_tmp;
			}
			else
			{
				copy[i] = tmp->cpy;
				i++;
			}
			tmp = tmp->next;
		}
		if (flag == 0)
			break ;
	}
	copy[i] = NULL;
	return (copy);
}

static int	exp_util(char tmp, int flg)
{
	write(1, &tmp, 1);
	if (!flg)
		write(1, "\"", 1);
	return (1);
}

static void	free_copy(char **copy)
{
	if (copy)
		free(copy);
}

void	print_exp(t_shelgon *shell)
{
	char	**copy;
	int		i;
	int		j;
	int		flg;

	copy = sort_exp(shell, copy);
	j = -1;
	while (copy && copy[++j])
	{
		i = 0;
		flg = 0;
		ft_putstr_fd("declare -x ", 1);
		while (copy[j][i])
		{
			if (copy[j][i] == '=')
				flg = exp_util(copy[j][i], flg);
			else
				write(1, &copy[j][i], 1);
			i++;
		}
		if (flg)
			write(1, "\"", 1);
		printf("\n");
	}
	free_copy(copy);
}
