#include "../inc/minishell.h"

void	parser(t_token **head)
{
	t_token	*cursor;
	int		is_pipe;

	cursor = *head;
	is_pipe = 0;
	if (!cursor)
		printf("uhoh");
	while (cursor)
	{
		printf("%i\n", cursor->type);
		if (cursor->type == PIPE)
			is_pipe = 1;
		cursor = cursor->next;
	}
	if (!is_pipe)
		printf("SINGLE COMMAND\n");
}

//Need to add error management of if it cant find a command
t_ast	*create_ast(t_token *head)
{
	t_token *cursor;
	t_ast	*root;

	cursor = head;
	while (cursor)
	{
		if (cursor->type == PIPE)
		{
			root = new_pipe_node();
		}
		else if (cursor->type == REDIR_IN || cursor->type == REDIR_OUT
				|| cursor->type == REDIR_APP || cursor->type == REDIR_DELIMIT)
		{
			root = new_redir_node(cursor);
		}
		else
		{
			root = new_word_node(cursor);
		}
		
	}
	return (NULL);
}