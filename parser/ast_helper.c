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
	//new->value = token->value;
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

void	print_tree(t_ast *root)
{
	t_ast	*cursor;
	t_ast	*temp;

	//printf("entering print tree function\n");
	cursor = root;
	//printf("root node: ");
	if (root)
	{
		printf("Type of node: %d Value of node: %s\n", cursor->type, cursor->value);
		printf("GOING LEFT:");
		print_tree(root->left);
		printf("GOING RIGHT: ");
		print_tree(root->right);
		printf("finished subtree\n");
	}
	else
		printf("(null)\n");
	return ;
}

t_ast	*connect_subtree(t_ast *root, t_ast *l_subtree, t_ast *r_subtree)
{
	t_ast	*combined_tree;

	if (!root)
	{
		combined_tree = r_subtree;
		combined_tree->left = NULL;
	}
	else
	{
		combined_tree = root;
		combined_tree->left = l_subtree;
		combined_tree->right = r_subtree;
	}
	return (combined_tree);
}
