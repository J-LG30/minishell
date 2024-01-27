/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:39:12 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:19:17 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Applies function f to content of each node and creates/returns 
//new list resulting from application of function
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (0);
	while (lst != NULL)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, new);
		lst = lst -> next;
	}
	return (head);
}
