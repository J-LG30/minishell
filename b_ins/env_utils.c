/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:32:23 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/16 19:11:01 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_env	*ms_lstlast(t_env *lst)
{
	t_env	*ls;

	ls = lst;
	if (ls != NULL)
	{
		while (ls->next != NULL)
			ls = ls->next;
	}
	return (ls);
}

t_env	*ms_lstadd(char *s)
{
	t_env	*node;
	node = malloc(sizeof(t_env));
	if (node)
	{
		node->vr = ft_strdup(s);
		node->cpy = node->vr;
		node->prnt = 1;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	ms_addnode(t_env **arr, char *s)
{
	t_env	*node;
	t_env	*temp;

	node = ms_lstadd(s);
	if (!node)
		return ;
	if (*arr == NULL)
		(*arr) = node;
	else
	{
		temp = ms_lstlast(*arr);
		node->prev = temp;
		temp->next = node;
	}
}

void	print_list(t_env *arr)
{
	while (arr)
	{
		if (arr->prnt)
			printf("%s\n", arr->vr);
		arr = arr->next;
	}
}
