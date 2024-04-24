/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:03 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/23 17:31:50 by jle-goff         ###   ########.fr       */
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
	if (((*shelgon)->current->type == REDIR_IN && (*shelgon)->current->next->type != WORD)
		|| ((*shelgon)->current->type == REDIR_APP && (*shelgon)->current->next->type != WORD))
	{
		free_ast((*shelgon)->tree);
		(*shelgon)->tree = NULL;
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
		return (NULL);
	}
	if (((*shelgon)->current->type == REDIR_IN && (*shelgon)->current->next->type == WORD)
		|| ((*shelgon)->current->type == REDIR_APP && (*shelgon)->current->next->type == WORD))
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
	int		next;

	type = (*shelgon)->current->type;
	if (((*shelgon)->current->type == REDIR_OUT && (*shelgon)->current->next->type != WORD)
		|| ((*shelgon)->current->type == REDIR_DELIMIT && (*shelgon)->current->next->type != WORD))
	{
		free_ast((*shelgon)->tree);
		(*shelgon)->tree = NULL;
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
		return (NULL);
	}
	if (((*shelgon)->current->type == REDIR_OUT && (*shelgon)->current->next->type == WORD)
		|| ((*shelgon)->current->type == REDIR_DELIMIT && (*shelgon)->current->next->type == WORD))
	{
		new = new_redir_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next->next;
		return (new);
	}
	return (NULL);
}