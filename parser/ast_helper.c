/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:25 by jle-goff          #+#    #+#             */
/*   Updated: 2024/03/17 15:39:38 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast *new_node_init()
{
	t_ast *new;

	new = malloc(sizeof(t_ast) * 1);
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->type = -1;
	new->value = NULL;
	new->in_fd = -1;
	new->out_fd = -1;
	return (new);
}

t_ast	*new_pipe_node()
{
	t_ast *new;

	new = new_node_init();
	if (!new)
		return (NULL);
	new->type = PIPE;
	return (new);
}

//idk if i need to memcpy the string to the node or if 
//just pointing to the token memory works tbc
t_ast	*new_word_node(t_token *token)
{
	t_ast *new;

	new = new_node_init();
	if (!new)
		return (NULL);
	new->type = token->type;
	new->value = token->value;
	return (new);
}

t_ast	*new_redir_node(t_token *token)
{
	t_ast *new;

	new = new_node_init();
	if (!new)
		return (NULL);
	new->type = token->type;
	new->value = token->next->value;
	return (new);
}

t_ast	*new_env_node(t_token *token)
{
	t_ast	*new;

	new = new_node_init();
	if (!new)
		return (NULL);
	new->type = ENV;
	new->value = token->value;
	return (new);
}

t_ast	*new_end_node()
{
	t_ast	*new;
	if (!new)
		return (NULL);
	new->type = END;
	return (new);
}

// void	print_tree(t_ast *root)
// {
// 	t_ast	*cursor;
// 	t_ast	*temp;

// 	//printf("entering print tree function\n");
// 	cursor = root;
// 	//printf("root node: ");
// 	if (root)
// 	{
// 		printf("Type of node: %d Value of node: %s\n", cursor->type, cursor->value);
// 		printf("GOING LEFT:");
// 		print_tree(root->left);
// 		printf("GOING RIGHT: ");
// 		print_tree(root->right);
// 		printf("finished subtree\n");
// 	}
// 	else
// 		printf("(null)\n");
// 	return ;
// }

t_ast	*connect_subtree(t_ast *root, t_ast *subtree, t_shelgon **shelgon)
{
	t_ast	*temp;

	if (!(*shelgon)->tree)
	{
		(*shelgon)->tree = subtree;
		subtree->left = NULL;
		subtree->right = NULL;
	}
	else
	{
		if ((*shelgon)->tree && subtree->type == PIPE)
		{
			temp = (*shelgon)->tree;
			while (temp->right && temp->right->type == PIPE)
				temp = temp->right;
			temp = subtree;
			
		}
		else if ((*shelgon)->tree->type == PIPE && subtree->type == WORD)
		{
			
		}
		if (subtree->type == WORD && (*shelgon)->cmd_root == 0)
		{
			printf("PUTTING WORD AS COMMAND\n");
			temp = (*shelgon)->tree;
			(*shelgon)->tree = subtree;
			subtree->left = temp;
			(*shelgon)->cmd_root = 1;
		}
		else
		{
			printf("!!!!!!!!!!!!!!!\n");
			temp = (*shelgon)->tree;
			if (subtree->type == REDIR_APP || subtree->type == REDIR_DELIMIT
				|| subtree->type == REDIR_IN || subtree->type == REDIR_OUT)
			{
				while (temp->left)
					temp = temp->left;
				temp->left = subtree;
			}
			else if (subtree->type == WORD || subtree->type == ENV)
			{
				while (temp->right)
					temp = temp->right;
				temp->right = subtree;
			}
		}
	}
	return ((*shelgon)->tree);
}
