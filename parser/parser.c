#include "../inc/minishell.h"

t_ast	*create_ast(t_token *head, t_ast *root)
{
	t_token *cursor;

	cursor = head;
	while (cursor)
	{
		printf("%i\n", cursor->type);
		if (cursor->type == END)
		{
			root = new_end_node();
			return (root);
		}
		else if (cursor->type == PIPE)
		{
			root = new_pipe_node();
			root->left = create_ast(cursor->prev, root->left);
			root->right = create_ast(cursor->next, root->right);
			
		}
		else if (cursor->type == REDIR_IN || cursor->type == REDIR_OUT
				|| cursor->type == REDIR_APP || cursor->type == REDIR_DELIMIT)
		{
			root = new_redir_node(cursor);
			root->left = create_ast(cursor->prev, root->left);
			root->right = create_ast(cursor->next, root->right);
		}
		else if (cursor->type == ENV)
		{
			root = new_env_node(cursor);
			root->left = create_ast(cursor->prev, root->left);
			root->right = create_ast(cursor->next, root->right);
		}
		else
		{
			root = new_word_node(cursor);
			//root->left = create_ast(cursor->prev, root->left);
			root->right = create_ast(cursor->next, NULL);
		}
		
	}
	return (root);
}

t_ast	*parser(t_token **head)
{
	t_ast	*node;
	t_ast	*ast_tree;

	ast_tree = create_ast(*head, node);
	if (!ast_tree)
		return (NULL);	
	return (ast_tree);
}