/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:50:28 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/23 17:32:31 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_redir(t_ast *node)
{
	if (node->type == REDIR_IN || node->type == REDIR_OUT
		|| node->type == REDIR_DELIMIT || node->type == REDIR_APP)
	{
		return (1);
	}
	return (0);
}

void	add_word_tree(t_ast *subtree, t_shelgon **shelgon)
{
	t_ast	*temp;
	t_ast	*redir_temp;

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
	{
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
		else if ((*shelgon)->cmd_root == 2)
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
}

t_ast	*connect_subtree(t_ast *root, t_ast *subtree,
							t_shelgon **shelgon, int DIR)
{
	t_ast	*temp;

	if (!(*shelgon)->tree)
	{
		(*shelgon)->tree = subtree;
		subtree->left = NULL;
		subtree->right = NULL;
	}
	else if (subtree->type == WORD)
		add_word_tree(subtree, shelgon);
	else
	{
		temp = (*shelgon)->tree;
		while (temp->right && temp->right->type == PIPE)
			temp = temp->right;
		if (subtree->type == PIPE)
			temp->right = subtree;
		else
		{
			if (temp->type == PIPE
				&& ((*shelgon)->cmd_root == 2 || (*shelgon)->cmd_root == 3))
			{
				if (!temp->right)
					temp->right = subtree;
				else
				{
					temp = temp->right;
					while (temp->left)
						temp = temp->left;
					temp->left = subtree;
				}
			}
			else
			{
				while (temp->left)
					temp = temp->left;
				temp->left = subtree;
			}
		}
	}
	return ((*shelgon)->tree);
}