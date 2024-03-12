#include "../inc/minishell.h"

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

	ast_tree = create_expression(*head);
	if (!ast_tree)
		return (NULL);	
	return (ast_tree);
}