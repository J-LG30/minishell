#include "../inc/minishell.h"

t_token	*ft_tokenlast(t_token *lst)
{
	t_token	*next;

	if (lst == NULL)
		return (0);
	next = lst -> next;
	while (next != NULL)
	{
		lst = next;
		next = lst -> next;
	}
	return (lst);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*cursor;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			cursor = ft_tokenlast(*lst);
			cursor -> next = new;
		}
	}
}