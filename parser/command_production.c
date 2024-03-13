#include "../inc/minishell.h"

// command_word -> WORD
t_ast   *command_word(t_shelgon **shelgon)
{
	t_ast	*new;

	printf("in command_word\n");
	if ((*shelgon)->current->type == WORD)
	{
		new = new_word_node((*shelgon)->current);
		(*shelgon)->current = (*shelgon)->current->next;
		return (new);
	}
	return (NULL);
}

// command_prefix -> redirectin
//         | command_prefix redirectin
//         | redirectout
//         | command_prefix redirectout
t_ast   *command_prefix(t_shelgon **shelgon)
{
	t_ast	*cmd_prefix;
	t_ast	*subtree;
	t_token	*temp;
	int		status;
	
	printf("entering command prefix function\n");

	cmd_prefix = NULL;
	temp = (*shelgon)->current;
	while (1)
	{
		status = 0;
		subtree = create_redirectin(shelgon);
		if (subtree)
		{
			temp = (*shelgon)->current;
			cmd_prefix = connect_subtree(cmd_prefix, NULL, subtree);
			if (!cmd_prefix)
				return (NULL);
			status = 1;
		}
		else
			(*shelgon)->current = temp;
		printf("TYPE OF CURRENT TOKEN: %d\n", (*shelgon)->current->type);
		subtree = create_redirectout(shelgon);
		if (subtree)
		{
			temp = (*shelgon)->current;
			cmd_prefix = connect_subtree(cmd_prefix, NULL, subtree);
			if (!cmd_prefix)
				return (NULL);
			status = 1;
		}
		else
			(*shelgon)->current = temp;
		if (!status)
			break ;
	}
	printf("finished prefix check\n");
	return (cmd_prefix);
}

// command_suffix -> redirectin
//         | command_suffix redirectin
//         | redirectout
//         | command_suffix redirectout
//         | command_word
t_ast   *command_suffix(t_shelgon **shelgon)
{
	t_ast	*cmd_suffix;
	t_ast	*subtree;
	t_token	*temp;
	int		status;
	
	cmd_suffix = NULL;
	temp = (*shelgon)->current;
	while (1)
	{
		status = 0;
		subtree = create_redirectin(shelgon);
		if (subtree)
		{
			temp = (*shelgon)->current;
			cmd_suffix = connect_subtree(cmd_suffix, NULL, subtree);
			if (!cmd_suffix)
				return (NULL);
			status = 1;
		}
		else
			(*shelgon)->current = temp;
		subtree = create_redirectout(shelgon);
		if (subtree)
		{
			temp = (*shelgon)->current;
			cmd_suffix = connect_subtree(cmd_suffix, NULL, subtree);
			if (!cmd_suffix)
				return (NULL);
			status = 1;
		}
		else
			(*shelgon)->current = temp;
		subtree = command_word(shelgon);
		if (subtree)
		{
			temp = (*shelgon)->current;
			cmd_suffix = connect_subtree(cmd_suffix, NULL, subtree);
			if (!cmd_suffix)
				return (NULL);
			status = 1;
		}
		else
			(*shelgon)->current = temp;
		if (!status)
			break ;
	}
	return (cmd_suffix);
}