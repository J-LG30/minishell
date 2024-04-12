/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:34:42 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/12 16:06:54 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_env(t_env *var)
{
	while (var->next)
	{
		free(var->vr);
		var = var->next;
	}
	free(var);
}

void	env(char **envp, int flg)
{
	t_env	*var;
	int		i;

	var = malloc(sizeof(t_env));
	if (!var)
		return ;
	i = 0;
	var = NULL;
	while (envp[i])
	{
		ms_addnode(&var, envp[i]);
		i++;
	}
	if (flg)
		print_list(var);
}
