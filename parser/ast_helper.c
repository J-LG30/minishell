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
		if (subtree->type == WORD && (*shelgon)->cmd_root == 0)
		{
			printf("PUTTING WORD AS COMMAND\n");
			temp = (*shelgon)->tree;
			(*shelgon)->tree = subtree;
			subtree->left = temp;
			//subtree->right = NULL;
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
				//temp->right = NULL;
			}
			else if (subtree->type == WORD || subtree->type == ENV)
			{
				while (temp->right)
					temp = temp->right;
				temp->right = subtree;
				//temp->left = NULL;
			}
		}
	}
	return ((*shelgon)->tree);
}

// t_ast	*connect_subtree(t_ast *root, t_ast *subtree, t_shelgon **shelgon)
// {
// 	t_ast	*new;
// 	t_ast	*temp;
// 	t_ast	*cursor;

// 	if (!root)
// 	{
// 		new = subtree;
// 		new->left = NULL;
// 		new->right = NULL;
// 	}
// 	else
// 	{
// 		if (subtree->type == WORD && (*shelgon)->cmd_root == 0)
// 		{
// 			temp = root;
// 			root = subtree;
// 			root->left = temp;
// 		}
// 		else
// 		{
// 			new = root;
// 			temp = new;
// 			//printf("root is valid in connect trees\n");
// 			if (subtree->type == REDIR_APP || subtree->type == REDIR_DELIMIT
// 				|| subtree->type == REDIR_IN || subtree->type == REDIR_OUT)
// 			{
// 				while (temp->left)
// 					temp = temp->left;
// 				temp->left = subtree;
// 				//temp->left->left = NULL;
// 				//temp->right->right = NULL;
// 				temp->right = NULL;
// 			}
// 			else if (subtree->type == WORD || subtree->type == ENV)
// 			{
// 				while (new->right)
// 					new = new->right;
// 				temp->right = subtree;
// 				//temp->left->left = NULL;
// 				//temp->right->right = NULL;
// 				temp->left = NULL;
// 			}
// 		}
// 	}
// 	return (new);
// }
