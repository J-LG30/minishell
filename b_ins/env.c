/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:34:42 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/26 17:15:11 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static void	free_env(t_env *var)
// {
// 	while (var->next)
// 	{
// 		free(var->vr);
// 		var = var->next;
// 	}
// 	free(var);
// }

t_env	*env(t_shelgon *shell, char **envp, int flg, int retexit)
{
	t_env	*var;
	int		i;

	if (flg)
	{
		i = 0;
		var = NULL;
		while (envp[i])
		{
			ms_addnode(&var, envp[i]);
			i++;
		}
		return (var);
	}
	else
		print_list(shell->env);
	shell->status = 0;
	if (retexit)
		return (NULL);
	free_all(shell, shell->exe, BTIN);
	exit (0);
}
