/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:32 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/28 14:41:39 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			cursor->next = new;
			new->prev = cursor;
		}
	}
}

//malloc error management
t_token	*ft_new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->error = -1;
	new->next = NULL;
	new->prev = NULL;
	new->type = 0;
	new->value = NULL;
	new->copy = NULL;
	return (new);
}

t_token	*token_type_exists(t_token *lst, int type)
{
	t_token	*cursor;

	cursor = lst;
	if (lst)
	{
		while (cursor)
		{
			if (cursor->type == type)
				return (cursor);
			cursor = cursor->next;
		}
	}
	return (NULL);
}

int	is_token_type(t_token *token, int type)
{
	if (token)
	{
		if (token->type == type)
			return (1);
	}
	return (0);
}
