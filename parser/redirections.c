#include "../inc/minishell.h"

// redirectin -> REDIR_IN command_word
//         | REDIR_APP command_word
t_ast	*create_redirectin(t_token *head)
{
	if ((head->type == REDIR_IN && head->next->type == WORD))
		|| ((head->type == REDIR_APP && head->next->type == WORD))
		return (new_redir_node(head));
	return (NULL);
}

// redirectout → REDIR_OUT command_word
//         | REDIR_DELIMIT command_word
t_ast	*create_redirectout(t_token *head)
{
	if ((head->type == REDIR_OUT && head->next->type == WORD))
		|| ((head->type == REDIR_DELIMIT && head->next->type == WORD))
		return (new_redir_node(head));
	return (NULL);
}