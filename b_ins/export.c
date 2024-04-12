/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:17:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/12 16:07:34 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/* 
int	main(int ac, char **av, char **envp)
{
	t_exp	*exp;
	int		i;
	
	(void)ac;
	exp = malloc(sizeof(t_exp));
	if (!exp)
		return (1);
	i = 0;
	exp = NULL;
	while (envp[i])
	{
		ms_addnode(&exp, envp[i]);
		i++;
	}
	if (!av[1])
		print_list_exp(&exp);
	else
	{
		if (check_equal(av[1]))
		{
			ms_addnode(&exp, av[1]);
			ms_addnode(&env, av[1]);
		}
		else
			ms_addnode(&exp, av[1]);
	}
} */
