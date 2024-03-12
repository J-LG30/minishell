#include "../inc/minishell.h"

// redirectin -> REDIR_IN command_word
//         | REDIR_APP command_word
t_ast	*create_redirectin(t_token *head)
{
	t_ast	*current;

	current = head->current;
	if (!current || !current->next)
		return (NULL);
	if (current->type == REDIR_IN && current->next->type)
		//create tree node
}

// redirectout → REDIR_OUT command_word
//         | REDIR_DELIMIT command_word
t_ast	*create_redirectout(t_token *head)
{
	t_ast	*current;

	current = head->current;
	if (!current || !current->next)
		return (NULL);
	if (current->type == REDIR_IN && current->next->type)
		//create tree node
}