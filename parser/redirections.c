/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:03 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/17 17:10:40 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// redirectin -> REDIR_IN command_word
//         | REDIR_APP command_word
t_ast	*create_redirectin(t_shelgon **shelgon)
{
	t_ast	*new;
	int		type;

	type = (*shelgon)->current->type;
	if (type == REDIR_IN && type != WORD || type == REDIR_APP && type != WORD)
	{
		free_ast((*shelgon)->tree);
		(*shelgon)->tree = NULL;
		printf("DJShell: Syntax error near unexpected token\n");
		return (NULL);
	}
	if (type == REDIR_IN && type == WORD || type == REDIR_APP && type == WORD)
	{
		new = new_redir_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next->next;
		return (new);
	}
	return (NULL);
}

// redirectout → REDIR_OUT command_word
//         | REDIR_DELIMIT command_word
t_ast	*create_redirectout(t_shelgon **shelgon)
{
	t_ast	*new;
	int		type;

	type = (*shelgon)->current->type;
	if (type == REDIR_OUT && type != WORD || type == REDIR_DELIMIT && type != WORD)
	{
		free_ast((*shelgon)->tree);
		(*shelgon)->tree = NULL;
		printf("DJShell: Syntax error near unexpected token\n");
		return (NULL);
	}
	if (type == REDIR_OUT && type == WORD || type == REDIR_DELIMIT && type == WORD)
	{
		new = new_redir_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next->next;
		return (new);
	}
	return (NULL);
}
