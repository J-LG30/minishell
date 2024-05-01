/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:03 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/01 16:39:00 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// redirectin -> REDIR_IN command_word
//         | REDIR_APP command_word

void	print_syntax_error(t_shelgon **shelgon, t_token *cur)
{
	if ((*shelgon)->print_error == 1)
		return ;
	ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: ", 2);
	ft_putstr_fd("syntax error near unexpected token '", 2);
	if (cur->type == PIPE)
		ft_putstr_fd("|'\n", 2);
	else if (cur->type == REDIR_APP || cur->type == REDIR_IN)
		ft_putstr_fd("<'\n", 2);
	else if (cur->type == REDIR_DELIMIT || cur->type == REDIR_OUT)
		ft_putstr_fd(">'\n", 2);
	else if (cur->type == END)
		ft_putstr_fd("newline'\n", 2);
	(*shelgon)->print_error = 1;
}

t_ast	*create_redirectin(t_shelgon **shelgon)
{
	t_ast	*new;
	t_token	*cur;

	cur = (*shelgon)->current;
	if ((cur->type == REDIR_IN && cur->next->type != WORD)
		|| (cur->type == REDIR_APP && cur->next->type != WORD))
	{
		free_ast((*shelgon)->tree);
		(*shelgon)->tree = NULL;
		print_syntax_error(shelgon, cur->next);
		return (NULL);
	}
	if ((cur->type == REDIR_IN && cur->next->type == WORD)
		|| (cur->type == REDIR_APP && cur->next->type == WORD))
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
	t_token	*cur;

	cur = (*shelgon)->current;
	if ((cur->type == REDIR_OUT && cur->next->type != WORD)
		|| (cur->type == REDIR_DELIMIT && cur->next->type != WORD))
	{
		free_ast((*shelgon)->tree);
		(*shelgon)->tree = NULL;
		print_syntax_error(shelgon, cur->next);
		return (NULL);
	}
	if ((cur->type == REDIR_OUT && cur->next->type == WORD)
		|| (cur->type == REDIR_DELIMIT && cur->next->type == WORD))
	{
		new = new_redir_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next->next;
		return (new);
	}
	return (NULL);
}
