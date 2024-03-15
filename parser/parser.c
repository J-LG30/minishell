#include "../inc/minishell.h"

t_ast	*create_expression(t_token *head, t_shelgon **shelgon);

//command PIPE expression
t_ast	*expression_one(t_token *head, t_shelgon **shelgon)
{
	t_ast	*pipe_node;
	t_ast	*command_tree;
	t_ast	*combined_tree;
	t_ast 	*expression_tree;
	t_token	*temp;

	temp = (*shelgon)->current;
	pipe_node = new_pipe_node();
	if (!pipe_node)
		return (NULL);
	command_tree = create_command(head, shelgon);
	if (!command_tree)
	{
		//free pipe node
		(*shelgon)->current = temp;
		return (NULL);
	}
	(*shelgon)->current = (*shelgon)->current->next;
	expression_tree = create_expression(head, shelgon);
	if (!expression_tree)
	{
		//free pipe and command tree
		(*shelgon)->current = temp;
		return (NULL);
	}
	//combined_tree = connect_subtree(pipe_node, command_tree, expression_tree);
	combined_tree = connect_trees(pipe_node, command_tree);
	combined_tree = connect_trees(pipe_node, expression_tree);
	if (!combined_tree)
	{
		//free pipe node + command_tree + expression tree
		(*shelgon)->current = temp;
		return (NULL);
	}
	return (combined_tree);
}

//command
t_ast	*expression_two(t_token *head, t_shelgon **shelgon)
{
	t_ast	*command_tree;

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
	t_token *temp;

	printf("TYPE OF CURRENT TOKEN: %d\n", (*shelgon)->current->type);
	printf("in create expression\n");
	//temp = (*shelgon)->current;
	if (token_type_exists((*shelgon)->current, PIPE))
	{
		printf("entering expression 1\n");
		tree = expression_one(temp, shelgon);
		if (tree)
			return (tree);
	}
	else
	{
		printf("entering expression 2\n");
		//(*shelgon)->current = temp;
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