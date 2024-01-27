/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:04:41 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:02:36 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Deletes who list starting from *lst
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*head;

	if (*lst == NULL || del == NULL)
		return ;
	cursor = *lst;
	head = *lst;
	while (cursor != NULL)
	{
		head = head -> next;
		ft_lstdelone(cursor, del);
		cursor = head;
	}
	*lst = NULL;
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

void	del_int(void *content)
{
	free(content);
}

void	relink(t_list **head, t_list *node)
{
	t_list	*prev;

	prev = *head;
	if (*head == node)
	{
		*head = node -> next;
		return ;
	}
	while (prev -> next != node)
	{
		prev = prev -> next;
	}
	prev -> next = node -> next;
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

     ft_lstadd_back(&head, a);
     ft_lstadd_back(&head, b);
     ft_lstadd_back(&head, c);

	printf("Original List: ");
    printList(head);

    ft_lstclear(&head, &del_int);

    printf("Updated List: ");
    printList(head);
     return 0;
}
*/
