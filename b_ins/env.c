/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:34:42 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/19 17:50:56 by jle-goff         ###   ########.fr       */
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

t_env	*env(char **envp, int flg)
{
	t_env	*var;
	int		i;

	var = malloc(sizeof(t_env) * 1);
	if (!var)
		return (NULL);
	i = 0;
	var = NULL;
	while (envp[i])
	{
		ms_addnode(&var, envp[i]);
		i++;
	}
	if (flg)
		print_list(var);
	else
		return (var);
	exit (0);
}
