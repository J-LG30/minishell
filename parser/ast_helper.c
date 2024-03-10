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
	new->value = token->value;
}

