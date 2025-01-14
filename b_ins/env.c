/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:34:42 by davda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:11:39 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_env	*env_lstadd(char *s)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (node)
	{
		if (s && s[0])
		{
			node->vr = ft_strdup(s);
			node->cpy = ft_strdup(s);
			node->prnt = 1;
			node->next = NULL;
			node->prev = NULL;
		}
	}
	return (node);
}

static void	env_addnode(t_env **arr, char *s)
{
	t_env	*node;
	t_env	*temp;

	node = NULL;
	if (s != NULL && s[0] != '\0')
		node = env_lstadd(s);
	if (!node)
		return ;
	if (*arr == NULL)
		(*arr) = node;
	else
	{
		temp = ms_lstlast(*arr);
		temp->next = node;
		node->prev = temp;
	}
}

t_env	*env(t_shelgon *shell, int flg, int retexit)
{
	t_env	*var;
	int		i;

	if (flg)
	{
		i = 0;
		var = NULL;
		while (shell->envr && shell->envr[i] != NULL)
		{
			env_addnode(&var, shell->envr[i]);
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
