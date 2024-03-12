#include "../inc/minishell.h"

//command PIPE expression
t_ast	*expression_one(t_token *head, t_shelgon **t_shelgon)
{
	t_ast	*pipe_node;
	t_ast	*command_tree;

	pipe_node = new_pipe_node();
	if (!pipe_node)
		return (NULL);
	command_tree = create_command(head);
	if (!command_tree)
		return (NULL);
	return (command_tree);
}

//command
t_ast	*expression_two(t_token *head, t_shelgon **shelgon)
{
	t_ast	*command_tree;

	printf("entering expression two function\n");
	command_tree = create_command(head);
	if (!command_tree)
		return (NULL);
	return (command_tree);
}	

//expression → command
//			| command PIPE expression
t_ast	*create_expression(t_token *head, t_shelgon **shelgon)
{
	t_ast	*tree;
	t_token *temp;

	temp = (*shelgon)->current;
	if (token_type_exists(head, PIPE))
	{
		tree = expression_one(temp, shelgon);
		if (tree)
			return (tree);
	}
	else
	{
		printf("entering else expression\n");
		(*shelgon)->current = temp;
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

	//printf("%s\n", (*shelgon)->current->value);
	ast_tree = create_expression(head, shelgon);
	if (!ast_tree)
		return (NULL);
	return (ast_tree);
}