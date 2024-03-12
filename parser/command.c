#include "../inc/minishell.h"

//command → command_prefix command_word command_suffix

// command_word -> WORD
t_ast   *command_word(t_token *head)
{

}

// command_prefix -> redirectin
//         | command_prefix redirectin
//         | redirectout
//         | command_prefix redirectout
t_ast   *command_prefix(t_token *head)
{

}

// command_suffix -> redirectin
//         | command_suffix redirectin
//         | redirectout
//         | command_suffix redirectout
//         | command_word
t_ast   *command_suffix(t_token *head)
{

}

// command → command_prefix command_word command_suffix
//         | command_prefix command_word
//         | command_word command_suffix
//         | command_word
t_ast	*create_command(t_token *head)
{
	
}