/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:29:05 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/29 20:37:18 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sort_exp(t_shelgon *shell)
{
	t_env	*tmp;
	char	*var_tmp;

	tmp = shell->env;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->cpy, tmp->next->cpy) > 0)
		{
			var_tmp = tmp->cpy;
			tmp->cpy = tmp->next->cpy;
			tmp->next->cpy = var_tmp;
			tmp = shell->env;
		}
		else
			tmp = tmp->next;
	}
}

static int	exp_util(char tmp, int flg)
{
	write(1, &tmp, 1);
	if (!flg)
		write(1, "\"", 1);
	return (1);
}

void	print_exp(t_shelgon *shell)
{
	t_env	*tmp;
	int		i;
	int		flg;

	sort_exp(shell);
	tmp = shell->env;
	while (tmp)
	{
		i = 0;
		flg = 0;
		ft_putstr_fd("declare -x ", 1);
		while (tmp->cpy[i])
		{
			if (tmp->cpy[i] == '=')
				flg = exp_util(tmp->cpy[i], flg);
			else
				write(1, &tmp->cpy[i], 1);
			i++;
		}
		if (flg)
			write(1, "\"", 1);
		printf("\n");
		tmp = tmp->next;
	}
}
