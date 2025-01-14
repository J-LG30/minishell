/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:29:05 by davda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:24:21 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ms_lstsize(t_env *lst)
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

	copy = NULL;
	copy = sort_exp(shell, copy);
	j = -1;
	while (copy && copy[++j])
	{
		i = 0;
		flg = 0;
		ft_putstr_fd("declare -x ", 1);
		while (copy[j] && copy[j][i])
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
