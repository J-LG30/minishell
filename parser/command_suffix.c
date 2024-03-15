#include "../inc/minishell.h"

//redirectin command_suffix
t_ast	*redirin_suffix(t_shelgon **shelgon)
{
	t_ast	*redirin;
	t_ast	*suffix;
	t_ast	*new_tree;
	t_token	*temp;

	printf("entered redirin_suffix\n");
	temp = (*shelgon)->current; // Save current token
	redirin = create_redirectin(shelgon);
	if (!redirin)
	{
		(*shelgon)->current = temp; // Restore token position if failed
		return (NULL);
	}
	temp = (*shelgon)->current;
	suffix = command_suffix(shelgon);
	if (!suffix)
	{
		(*shelgon)->current = temp;
		//new_tree = connect_subtree(NULL, redirin, NULL); // No suffix, connect redirin only
		new_tree = connect_trees(NULL, redirin);
	}
	else
	{
		//new_tree = connect_subtree(NULL, redirin, suffix);
		new_tree = connect_trees(NULL, redirin);
		new_tree = connect_trees(new_tree, suffix);
	}
	return new_tree;
}

//redirectout command_suffix
t_ast	*redirout_suffix(t_shelgon **shelgon)
{
    t_ast	*redirout;
    t_ast	*suffix;
    t_ast	*new_tree;
    t_token	*temp;

	printf("entered redirout_suffix\n");
    temp = (*shelgon)->current; // Save current token
    redirout = create_redirectout(shelgon);
    if (!redirout) 
	{
        (*shelgon)->current = temp; // Restore token position if failed
        return (NULL);
    }
	temp = (*shelgon)->current;
    suffix = command_suffix(shelgon);
    if (!suffix) 
	{
		(*shelgon)->current = temp;
        //new_tree = connect_subtree(NULL, redirout, NULL); // No suffix, connect redirout only
		new_tree = connect_trees(NULL, redirout);
    } 
	else 
	{
        //new_tree = connect_subtree(NULL, redirout, suffix);
		new_tree = connect_trees(NULL, redirout);
		new_tree = connect_trees(new_tree, suffix);
    }
    return new_tree;
}

//command_word command_suffix
t_ast	*word_suffix(t_shelgon **shelgon)
{
	t_ast	*cmd_word;
	t_ast	*suffix;
	t_ast	*new_tree;
	t_token	*temp;

	printf("entered word_suffix\n");
	temp = (*shelgon)->current;
	cmd_word = command_word(shelgon);
	if (!cmd_word)
	{
		(*shelgon)->current = temp;
		return (NULL);
	}
	temp = (*shelgon)->current;
	suffix = command_suffix(shelgon);
	if (!suffix)
	{
		//printf("234234\n");
		(*shelgon)->current = temp;
		return (cmd_word);
	}
	else
	{
		//new_tree = connect_subtree(NULL, cmd_word, suffix);
		new_tree = connect_trees(NULL, cmd_word);
		new_tree = connect_trees(cmd_word, suffix);
	}
	return new_tree;
}

// command_suffix -> redirectin command_suffix
//         | redirectout command_suffix
//         | command_word command_suffix
//         | redirectin
//         | redirectout
//         | command_word
t_ast	*command_suffix(t_shelgon **shelgon)
{
    t_token	*temp;

	temp = (*shelgon)->current;
    if (is_token_type((*shelgon)->current, REDIR_IN) || is_token_type((*shelgon)->current, REDIR_APP)) 
	{
        return redirin_suffix(shelgon);
    } 
	else if (is_token_type((*shelgon)->current, REDIR_OUT) || is_token_type((*shelgon)->current, REDIR_DELIMIT)) 
	{
        return redirout_suffix(shelgon);
    } 
	else if (is_token_type((*shelgon)->current, WORD)) 
	{
        return word_suffix(shelgon);
    } 
	else 
	{
        (*shelgon)->current = temp;
    }
	return (NULL);
}