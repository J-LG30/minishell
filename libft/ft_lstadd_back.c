/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:37:22 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/21 12:22:16 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cursor;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			cursor = ft_lstlast(*lst);
			cursor -> next = new;
		}
	}
}

/*
void printList(t_list *head)
{
    t_list	*temp = head;
	char	*c;

    //iterate the entire linked list and print the data
    while(temp != NULL)
    {
		c = temp->content;
         printf("%s->", c);
         temp = temp->next;
    }
    printf("NULL\n");
}
int main()
{
     t_list *head = NULL;

	 char *c1 = malloc(sizeof(char));
	 char *c2 = malloc(sizeof(char));
	 char *c3 = malloc(sizeof(char));

	 *c1 = 'a';
	 *c2 = 'b';
	 *c3 = 'c';
	 t_list	*a = ft_lstnew(c1);
	 t_list	*b = ft_lstnew(c2);
	 t_list	*c = ft_lstnew(c3);

     ft_lstadd_back(0, a);
     ft_lstadd_back(&head, b);
     ft_lstadd_back(&head, c);

     printList(head);

     return 0;
}
*/
