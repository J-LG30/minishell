#include "../inc/minishell.h"

// redirectin -> REDIR_IN command_word
//         | REDIR_APP command_word
t_ast	*create_redirectin(t_shelgon **shelgon)
{
	t_ast	*new;

	printf("entering redirin function\n");

	if (((*shelgon)->current->type == REDIR_IN && (*shelgon)->current->next->type == WORD)
		|| ((*shelgon)->current->type == REDIR_APP && (*shelgon)->current->next->type == WORD))
	{
		new = new_redir_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next->next;
		return (new);
		
	}
	return (NULL);
}

// redirectout → REDIR_OUT command_word
//         | REDIR_DELIMIT command_word
t_ast	*create_redirectout(t_shelgon **shelgon)
{
	t_ast	*new;

	printf("entering redirout function\n");

	if (((*shelgon)->current->type == REDIR_OUT && (*shelgon)->current->next->type == WORD)
		|| ((*shelgon)->current->type == REDIR_DELIMIT && (*shelgon)->current->next->type == WORD))
	{
		new = new_redir_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next->next;
		return (new);
	}
	return (NULL);
}