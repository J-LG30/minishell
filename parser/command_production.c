#include "../inc/minishell.h"

// command_word -> WORD
t_ast   *command_word(t_token *head)
{
	if (head->type == WORD)
		return(new_word_node(head));
	return (NULL);
}

// command_prefix -> redirectin
//         | command_prefix redirectin
//         | redirectout
//         | command_prefix redirectout
t_ast   *command_prefix(t_token *head)
{
	t_token	*cursor;
	t_ast	*cmd_prefix;
	
	cmd_prefix = create_redirectin(head);
	if (cmd_prefix)
		return (cmd_prefix);
	cmd_prefix = create_redirectout(head);
	if (cmd_prefix)
		return (cmd_prefix);
	
	return (NULL);
}

// command_suffix -> redirectin
//         | command_suffix redirectin
//         | redirectout
//         | command_suffix redirectout
//         | command_word
t_ast   *command_suffix(t_token *head)
{
	return (NULL);
}