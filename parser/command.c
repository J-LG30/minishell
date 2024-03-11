#include "../inc/minishell.h"

command → redirectin? WORD+ redirectout? 
        | redirectin? WORD+ literal redirectout?
t_ast	*create_command(t_token *head)
{
	
}