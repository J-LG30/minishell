/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:35 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:18:32 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Iterates through lst and applies function f on content of each node
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst -> next;
	}
}

/*
void	add(void *c)
{
	(*(char*)c)++;
}
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

     ft_lstadd_back(&head, a);
     ft_lstadd_back(&head, b);
     ft_lstadd_back(&head, c);

	 ft_lstiter(head, &add);

     printList(head);

     return 0;
}
*/
