/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:01:56 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/20 13:58:56 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new -> next = *lst;
	*lst = new;
}
/*
//Test code for checking linked lists
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

     ft_lstadd_front(&head, a);
     ft_lstadd_front(&head, b);
     ft_lstadd_front(&head, c);

     printList(head);

     return 0;
}
*/
