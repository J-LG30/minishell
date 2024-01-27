/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:43 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 19:56:52 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Returns how many nodes in a linked list
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*cursor;

	if (lst == NULL)
		return (0);
	size = 0;
	cursor = lst;
	while (cursor != 0)
	{
		size++;
		cursor = cursor -> next;
	}
	return (size);
}
