#include "../inc/minishell.h"

//redirectin command_suffix
t_ast	*redirin_suffix(t_shelgon **shelgon)
{
	t_ast	*redirin;
	t_ast	*suffix;
	t_ast	*new_tree;
	t_node	*temp;

	temp = (*shelgon)->current;
	redirin = create_redirectin(shelgon);
	if (!redirin)
		return (NULL);
	suffix = command_suffix(shelgon);
	if (!suffix)
		return (redirin);
	new_tree = connect_subtree()

}

//redirectout command_suffix
t_ast	*redirout_suffix(t_shelgon **shelgon)
{

}

//command_word command_suffix
t_ast	*word_suffix(t_shelgon **shelgon)
{
	t_ast	*cmd_word;
	t_ast	*suffix;
	t_ast	*new_tree;
	t_node	*temp;

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
		(*shelgon)->current = temp;
		return (cmd_word);
	}
	new_tree = connect_subtree()
}

// command_suffix -> redirectin command_suffix
//         | redirectout command_suffix
//         | command_word command_suffix
//         | redirectin
//         | redirectout
//         | command_word
t_ast	*command_suffix(t_shelgon **shelgon)
{
	t_ast	*redirout_tree;
	t_ast	*redirin_tree;
	t_ast	*cmd_word;
	t_ast	*full_tree;
	t_node	*temp;

	temp = (*shelgon)->current;
	redirin_tree = create_redirectout(shelgon);
	if (redirin_tree && (*shelgon)->current->next->type == END)
		return (redirin_tree);
	else if ()
}