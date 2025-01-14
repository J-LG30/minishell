/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:51 by jle-goff          #+#    #+#             */
/*   Updated: 2025/01/14 13:31:10 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	not_pipe_word2(t_ast *subtree, t_shelgon **shelgon,
			t_ast *temp, t_ast *redir_temp)
{
	if ((*shelgon)->cmd_root == 2)
	{
		redir_temp = temp->right;
		temp->right = subtree;
		if (redir_temp && redir_temp->type != WORD)
			subtree->left = redir_temp;
	}
	else if ((*shelgon)->cmd_root == 3)
	{
		redir_temp = temp->left;
		temp = temp->right;
		while (temp->right)
			temp = temp->right;
		temp->right = subtree;
	}
}

void	not_pipe_word(t_ast *subtree, t_shelgon **shelgon)
{
	t_ast	*temp;
	t_ast	*redir_temp;

	temp = (*shelgon)->tree;
	while (temp->right && temp->right->type == PIPE)
		temp = temp->right;
	redir_temp = temp->left;
	if ((*shelgon)->cmd_root == 0)
	{
		temp->left = subtree;
		subtree->left = redir_temp;
	}
	else if ((*shelgon)->cmd_root == 1)
	{
		temp = temp->left;
		while (temp->right)
			temp = temp->right;
		temp->right = subtree;
	}
	else
		not_pipe_word2(subtree, shelgon, temp, redir_temp);
}

void	add_word_tree(t_ast *subtree, t_shelgon **shelgon)
{
	t_ast	*temp;

	temp = (*shelgon)->tree;
	if ((*shelgon)->tree->type != PIPE)
	{
		if ((*shelgon)->cmd_root == 2)
		{
			(*shelgon)->tree = subtree;
			subtree->left = temp;
			subtree->right = NULL;
		}
		else if ((*shelgon)->cmd_root == 3)
		{
			while (temp->right)
				temp = temp->right;
			temp->right = subtree;
		}
	}
	else
		not_pipe_word(subtree, shelgon);
}
