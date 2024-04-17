/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:17:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/17 17:36:08 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sort_exp(t_env **arr)
{
	t_env	*tmp;
	char	*var_tmp;

	tmp = *arr;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->cpy, tmp->next->cpy) > 0)
		{
			var_tmp = tmp->cpy;
			tmp->cpy = tmp->next->cpy;
			tmp->next->cpy = var_tmp;
			tmp = *arr;
		}
		else
			tmp = tmp->next;
	}
}

static void	print_exp(t_env *env)
{
	t_env	*tmp;
	int		i;

	sort_exp(env);
	i = 0;
	tmp = env;
	while(tmp->next)
	{
		i = 0;
		printf("declare -x ");
		while (tmp->cpy[i])
		{
			if (tmp->cpy[i] == '=' && (tmp->cpy[i - 1] != '=' && tmp->cpy[i + 1] != '='))
			{
				write(1, &tmp->cpy[i], 1);
				write(1, "\"", 1);
				i++;
			}
			if (tmp->cpy[i + 1] == '\0')
			{
				write(1, &tmp->cpy[i], 1);
				write(1, "\"", 1);
			}
			else
				write(1, &tmp->cpy[i], 1);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

static void	add_export(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (parse_arg(args[i]))
		{
			if (args[i][ft_strlen(args[i - 1] == '=')])
			{
				
			}
		}
	}
}

void	export(t_branch *cmds, t_env *env)
{
	if (!cmds->full_cmd[1])
		print_exp(env);
	else
		add_export(cmds->full_cmd, env);
}
