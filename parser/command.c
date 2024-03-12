#include "../inc/minishell.h"

//command_prefix command_word command_suffix
t_ast	*command_one(t_token *head)
{
	t_ast	*cmd_prefix;
	t_ast	*cmd_word;
	t_ast	*cmd_suffix;

	cmd_prefix = command_prefix(head);
	if (!cmd_prefix)
		return (NULL);
	cmd_word = command_word(head);
	if (!cmd_word)
	{
		//free prefix ast
		return (NULL);
	}
	cmd_suffix = command_suffix(head);
	{
		//free prefix and word ast
		return (NULL);
	}
	if (cmd_prefix && cmd_word && cmd_suffix)
	{
			//connect all subtrees and return big subtree
	}
	return (NULL);
}

//command_prefix command_word
t_ast	*command_two(t_token *head)
{
	t_ast	*cmd_prefix;
	t_ast	*cmd_word;

	cmd_prefix = command_prefix(head);
	cmd_word = command_word(head);
	if (cmd_prefix && cmd_word)
	{
		//connect all subtrees and return big subtree
	}
	return (NULL);
}

//command_word command_suffix
t_ast	*command_three(t_token *head)
{
	t_ast	*cmd_word;
	t_ast	*cmd_suffix;

	cmd_word = command_word(head);
	cmd_suffix = command_suffix(head);
	if (cmd_word && cmd_suffix)
	{
		//connect all subtrees and return big subtree

	}
	return (NULL);
}

//command_word
t_ast	*command_four(t_token *head)
{
	t_ast	*cmd_word;

	cmd_word = command_word(head);
	if (cmd_word)
		return (cmd_word);
	return (NULL);
}

// command → command_prefix command_word command_suffix
//         | command_prefix command_word
//         | command_word command_suffix
//         | command_word
t_ast	*create_command(t_token *head)
{
	t_ast	*command;
	
	printf("entering create command function\n");
	command = command_one(head);
	if (command)
		return (command);
	command = command_two(head);
		return (command);
	command = command_three(head);
	if (command)
		return (command);
	command = command_four(head);
	if (command)
		return (command);
	return (NULL);
}