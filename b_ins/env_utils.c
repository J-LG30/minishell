/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:32:23 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/07 14:12:43 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ms_lstlast(t_env *lst)
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
	if (!node)
		return (NULL);
	if (node)
	{
		s = rm_quo(s);
		node->vr = ft_strdup(s);
		node->cpy = ft_strdup(s);
		free(s);
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
		temp->next = node;
		node->prev = temp;
	}
}

void	ms_addexp(t_env **arr, char *s)
{
	t_env	*node;
	t_env	*temp;

	node = ms_lstadd(s);
	node->prnt = 0;
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
	t_env	*tmp;

	tmp = arr;
	while (tmp)
	{
		if (tmp->vr && tmp->prnt)
			printf("%s\n", tmp->vr);
		tmp = tmp->next;
	}
}
