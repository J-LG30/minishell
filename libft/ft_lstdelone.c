/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:27:37 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/21 16:09:12 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst -> content);
	free(lst);
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

	relink(&head, a);

    ft_lstdelone(a, &del_int);

    printf("Updated List: ");
    printList(head);
     return 0;
}
*/
