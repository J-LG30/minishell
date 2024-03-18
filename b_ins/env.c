/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:34:42 by davda-si          #+#    #+#             */
/*   Updated: 2024/03/13 19:09:42 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_env(t_env *var)
{
	while (var->next)
	{
		free(var->data);
		var = var->next;
	}
	free(var);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*var;
	int		i;

	(void)ac;
	(void)av;
	var = malloc(sizeof(t_env));
	if (!var)
		return (1);
	i = 0;
	var = NULL;
	while (envp[i])
	{
		ms_addnode(&var, envp[i]);
		i++;
	}
	print_list(var);
	free_env(var);
}
