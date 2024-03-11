/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:42:27 by david             #+#    #+#             */
/*   Updated: 2024/03/11 18:27:19 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ms_lstadd(char *s)
{
	t_env	*node;
	node = malloc(sizeof(t_env));
	if (node)
	{
		node->vr = s;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	
ms_addnode(t_env **arr, char *s)
{
	t_env	*node;
	t_env	*temp;

	node = ms_lstadd(s);
	if (!node)
		return ;
	node->next = *arr;
	if (*arr != NULL)
		(*arr)->prev = node;
	(*arr) = node;
}
void	print_list(t_env *arr)
{
	while (arr)
	{
		printf("%s\n", arr->vr);
		arr = arr->next;
	}
}
