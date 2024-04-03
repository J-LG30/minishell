/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:42:32 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/02 14:52:54 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env(int ac, char **av, char **env)
{
	t_env	*arr;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	arr = NULL;
	while(env[i])
	{
		ms_addnode(&arr, env[i]);
		i++;
	}
	print_list(arr);
}
