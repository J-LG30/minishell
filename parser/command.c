#include "../inc/minishell.h"

//command_prefix command_word command_suffix
t_ast	*command_one(t_token *head, t_shelgon **shelgon)
{
	t_ast	*cmd_prefix;
	t_ast	*cmd_word;
	t_ast	*cmd_suffix;
	t_ast	*full_cmd;
	t_token	*temp;

	printf("entering command 1 function\n");
	printf("TYPE OF CURRENT TOKEN: %d\n", (*shelgon)->current->type);

	temp = (*shelgon)->current;
	printf("1\n");
	cmd_prefix = command_prefix(shelgon);
	printf("2\n");
	if (!cmd_prefix)
	{
		//printf("1\n");
		(*shelgon)->current = temp;
		return (NULL);
	}
	cmd_word = command_word(shelgon);
	if (!cmd_word)
	{
		//free prefix ast
		(*shelgon)->current = temp;
		return (NULL);
	}
	cmd_suffix = command_suffix(shelgon);
	if (!cmd_suffix)
	{
		//free prefix and word ast
		(*shelgon)->current = temp;
		return (NULL);
	}
	if (cmd_prefix && cmd_word && cmd_suffix)
	{
		full_cmd = connect_subtree(cmd_word, cmd_prefix, cmd_suffix);
		if (!full_cmd)
		{
			(*shelgon)->current = temp;
			//free cmd_suffix, cmd_word, cmd_prefix
			return (NULL);
		}
		return (full_cmd);
	}
	return (NULL);
}

//command_prefix command_word
t_ast	*command_two(t_token *head, t_shelgon **shelgon)
{
	t_ast	*cmd_prefix;
	t_ast	*cmd_word;
	t_ast	*full_cmd;
	t_token	*temp;

	printf("entering command 2 function\n");

	temp = (*shelgon)->current;
	cmd_prefix = command_prefix(shelgon);
	if (!cmd_prefix)
	{
		//printf("1\n");
		(*shelgon)->current = temp;
		return (NULL);
	}
	cmd_word = command_word(shelgon);
	if (!cmd_word)
	{
		//free cmd_prefix
		(*shelgon)->current = temp;
		return (NULL);
	}
	if (cmd_prefix && cmd_word)
	{
		full_cmd = connect_subtree(cmd_word, cmd_prefix, NULL);
		if (!full_cmd)
		{
			//free
			(*shelgon)->current = temp;
			return (NULL);
		}
		return (full_cmd);
	}
	return (NULL);
}

//command_word command_suffix
t_ast	*command_three(t_token *head, t_shelgon **shelgon)
{
	t_ast	*cmd_word;
	t_ast	*cmd_suffix;
	t_ast	*full_cmd;
	t_token	*temp;

	printf("entering command 3 function\n");

	temp = (*shelgon)->current;
	cmd_word = command_word(shelgon);
	if (!cmd_word)
	{
		(*shelgon)->current = temp;
		return (NULL);
	}
	cmd_suffix = command_suffix(shelgon);
	if (!cmd_suffix)
	{
		//free word ast
		(*shelgon)->current = temp;
		return (NULL);
	}
	if (cmd_word && cmd_suffix)
	{
		full_cmd = connect_subtree(cmd_word, NULL, cmd_suffix);
		if (!full_cmd)
		{
			//free
			return (NULL);
		}
		return (full_cmd);

	}
	return (NULL);
}

//command_word
t_ast	*command_four(t_token *head, t_shelgon **shelgon)
{
	t_ast	*cmd_word;
	t_token	*temp;

	printf("entering command 4 function\n");

	temp = (*shelgon)->current;
	cmd_word = command_word(shelgon);
	if (cmd_word)
		return (cmd_word);
	printf("its null\n");
	(*shelgon)->current = temp;
	return (NULL);
}

// command → command_prefix command_word command_suffix
//         | command_prefix command_word
//         | command_word command_suffix
//         | command_word
t_ast	*create_command(t_token *head, t_shelgon **shelgon)
{
	t_ast	*command;
	
	printf("entering create command function\n");
	command = command_one(head, shelgon);
	if (command)
		return (command);
	command = command_two(head, shelgon);
	if (command)
		return (command);
	command = command_three(head, shelgon);
	if (command)
		return (command);
	command = command_four(head, shelgon);
	if (command)
		return (command);
	return (NULL);
}