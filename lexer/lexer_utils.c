/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:18:27 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/03 14:14:11 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token *nullstr_helper(t_token *cursor, t_token *head, t_token *temp)
{
	while (cursor)
	{
		if (cursor->type == WORD && !cursor->value)
		{
			temp = cursor;
			if (cursor->next && cursor->prev->type == END)
			{
				head = cursor->next;
				head->prev = cursor->prev;
			}
			else if (cursor->next)
			{
				cursor->next->prev = cursor->prev;
				cursor->prev->next = cursor->next;
			}
			cursor = cursor->next;
			free(temp->copy);
			free(temp);
		}
		else
			cursor = cursor->next;
	}
	return (head);
}

t_token	*remove_nullstr_token(t_token *head)
{
	t_token	*cursor;
	t_token	*temp;

	cursor = head;
	if (!cursor)
		return (NULL);
	return (nullstr_helper(cursor, head, temp));
}

t_token	*check_tokens(t_token *head, t_shelgon *shelgon)
{
	t_token	*new_head;
	t_token	*cursor;

	cursor = head;
	while (cursor)
	{
		if (cursor->type == REDIR_DELIMIT && cursor->next
			&& cursor->next->type == WORD)
		{
			if (cursor->next->value)
				free(cursor->next->value);
			cursor->next->value = rm_quo(cursor->next->copy);
		}
		cursor = cursor->next;
	}
	new_head = remove_nullstr_token(head);
	cursor = new_head;
	while (cursor)
	{
		if (cursor->type == WORD)
			check_mult_tok(cursor, shelgon);
		cursor = cursor->next;
	}
	return (new_head);
}
