/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:40:09 by julietteleg       #+#    #+#             */
/*   Updated: 2024/03/18 14:56:04 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//recursively free ast. probably will have to update it
void	free_ast(t_ast	*tree)
{
	t_ast	*cursor;
	t_ast	*left;
	t_ast	*right;

	// if (!tree)
	// 	return ;
	cursor = tree;
	if (cursor)
	{
		left = cursor->left;
		right = cursor->right;
		free(cursor);
		free_ast(left);
		free_ast(right);
	}
	return ;
}

void	free_tokens(t_token *head)
{
	t_token *cursor;
	cursor = head;
	
	while (head->type != END)
	{
		if (cursor->value)
			free(cursor->value);
		head = head->next;
		free(cursor);
		cursor = head;
	}
	free(head);
}