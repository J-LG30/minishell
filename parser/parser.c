/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:44:07 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/25 17:46:18 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*create_expression(t_token *head, t_shelgon **shelgon);

//HANDLE FREE MALLOC ERROR
//command PIPE expression
t_ast	*expression_one(t_token *head, t_shelgon **shelgon)
{
	t_ast	*pipe_node;
	t_ast	*command_tree;
	t_ast	*combined_tree;
	t_ast	*expression_tree;
	t_token	*temp;

	(*shelgon)->cmd_root = 0;
	temp = (*shelgon)->current;
	pipe_node = new_pipe_node(temp);
	if (!pipe_node)
		return (NULL);
	connect_subtree((*shelgon)->tree, pipe_node, shelgon, RIGHT);
	command_tree = create_command(head, shelgon);
	if (!command_tree)
	{
		//free(pipe_node);
		(*shelgon)->current = temp;
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (NULL);
	}
	(*shelgon)->current = (*shelgon)->current->next;
	expression_tree = create_expression(head, shelgon);
	if (!expression_tree)
	{
		(*shelgon)->current = temp;
		return (NULL);
	}
	return ((*shelgon)->tree);
}

//command
t_ast	*expression_two(t_token *head, t_shelgon **shelgon)
{
	t_ast	*command_tree;

	(*shelgon)->cmd_root = 2;
	command_tree = create_command(head, shelgon);
	if (!command_tree)
		return (NULL);
	return (command_tree);
}

//expression → command
//			| command PIPE expression
t_ast	*create_expression(t_token *head, t_shelgon **shelgon)
{
	t_ast	*tree;
	t_token	*temp;

	if (token_type_exists((*shelgon)->current, PIPE))
	{
		tree = expression_one(temp, shelgon);
		if (tree)
			return (tree);
	}
	else
	{
		tree = expression_two(temp, shelgon);
		if (tree)
			return (tree);
	}
	return (NULL);
}

t_ast	*parser(t_token *head, t_shelgon **shelgon)
{
	t_ast	*node;
	t_ast	*ast_tree;

	ast_tree = create_expression(head, shelgon);
	if (!ast_tree)
		return (NULL);
	return (ast_tree);
}