/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_production.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:07 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/28 15:56:50 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// command_word -> WORD
t_ast	*command_word(t_shelgon **shelgon)
{
	t_ast	*new;
	t_token	*tmp;

	tmp = (*shelgon)->current;
	if (tmp->type == WORD && tmp->prev->type != REDIR_APP
		&& tmp->prev->type != REDIR_DELIMIT
		&& tmp->prev->type != REDIR_IN
		&& tmp->prev->type != REDIR_OUT)
	{
		new = new_word_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next;
		return (new);
	}
	return (NULL);
}
