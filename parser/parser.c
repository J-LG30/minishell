#include "../inc/minishell.h"

// t_ast	*create_ast(t_token *head, t_ast *root)
// {
// 	t_token *cursor;

// 	cursor = head;
// 	while (cursor)
// 	{
// 		printf("%i\n", cursor->type);
// 		if (cursor->type == END)
// 		{
// 			root = new_end_node();
// 			return (root);
// 		}
// 		else if (cursor->type == PIPE)
// 		{
// 			root = new_pipe_node();
// 			root->left = create_ast(cursor->prev, root->left);
// 			root->right = create_ast(cursor->next, root->right);
			
// 		}
// 		else if (cursor->type == REDIR_IN || cursor->type == REDIR_OUT
// 				|| cursor->type == REDIR_APP || cursor->type == REDIR_DELIMIT)
// 		{
// 			root = new_redir_node(cursor);
// 			root->left = create_ast(cursor->prev, root->left);
// 			root->right = create_ast(cursor->next, root->right);
// 		}
// 		else if (cursor->type == ENV)
// 		{
// 			root = new_env_node(cursor);
// 			root->left = create_ast(cursor->prev, root->left);
// 			root->right = create_ast(cursor->next, root->right);
// 		}
// 		else
// 		{
// 			root = new_word_node(cursor);
// 			root->left = create_ast(cursor->prev, root->left);
// 			root->right = create_ast(cursor->next, NULL);
// 		}
		
// 	}
// 	return (root);
// }

//command PIPE expression
t_ast	*expression_one(t_token *head)
{
	t_ast	*pipe_node;
	t_ast	*command_tree;

	pipe_node = new_pipe_node();
	if (!pipe)
		return (NULL);
	command_tree = create_command(head);
	if (!command_tree)
		return (NULL);
	return (command_tree);
}

//command
t_ast	*expression_two(t_token *head)
{

}	

//expression → command | command PIPE expression
t_ast	*create_expression(t_token *head)
{
	t_ast	*tree;

	if (token_type_exists(head, PIPE))
	{
		tree = expression_one(head);
		if (tree)
			return (tree);
	}
	else
	{
		tree = expression_two(head);
		if (tree)
			return (tree);
	}
	return (NULL);
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