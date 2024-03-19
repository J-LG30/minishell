/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:10 by jle-goff          #+#    #+#             */
/*   Updated: 2024/03/19 20:01:22 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//command_word command
t_ast	*command_one(t_token *head, t_shelgon **shelgon)
{
	t_ast	*cmd_word;
	t_token	*cursor;

        printf("in command 2\n");
	cursor = (*shelgon)->current;
	cmd_word = command_word(shelgon);
	if (!cmd_word)
	{
		(*shelgon)->current = cursor;
		return (NULL);
	}
        // if ((*shelgon)->cmd_root == 0)
        // {
        //         (*shelgon)->tree = cmd_word;
        //         (*shelgon)->cmd_root = 1;
        // }
        // else
        cmd_word = connect_subtree((*shelgon)->tree, cmd_word, shelgon, RIGHT);
		print_tree((*shelgon)->tree);
		if ((*shelgon)->cmd_root != 1)
                (*shelgon)->cmd_root = 1;
        create_command(head, shelgon);
	return (cmd_word);
}


//redirectout command
t_ast	*command_two(t_token *head, t_shelgon **shelgon)
{
	t_ast	*redirectout;
	t_token	*cursor;

        printf("in command 2\n");
	cursor = (*shelgon)->current;
	redirectout = create_redirectout(shelgon);
	if (!redirectout)
	{
		(*shelgon)->current = cursor;
		return (NULL);
	}
        redirectout = connect_subtree((*shelgon)->tree, redirectout, shelgon, LEFT);
        create_command(head, shelgon);
	return (redirectout);
}

//redirectin command
t_ast	*command_three(t_token *head, t_shelgon **shelgon)
{
	t_ast	*redirectin;
	t_token	*cursor;

        printf("in command 3\n");
	cursor = (*shelgon)->current;
	redirectin = create_redirectin(shelgon);
	if (!redirectin)
	{
		(*shelgon)->current = cursor;
		return (NULL);
	}
        redirectin = connect_subtree((*shelgon)->tree, redirectin, shelgon, LEFT);
        create_command(head, shelgon);
	return (redirectin);
}

// command → command_word command
//			|redirectin command
//          |redirectout command
t_ast	*create_command(t_token *head, t_shelgon **shelgon)
{
	t_ast	*cmd_word;
	t_ast	*redirin;
	t_ast	*redirout;
	t_ast	*command;
	
        //print_tree((*shelgon)->tree);
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
	return (NULL);
}

// t_ast	find_cmd_root(t_token *head, t_shelgon **shelgon)
// {
// 	t_ast	*cmd_word;
// 	t_token	*cursor;

// 	cmd_word = NULL;
// 	cursor = (*shelgon)->current;
// 	while ((*shelgon)->current->type != END)
// 	{
// 		cmd_word = command_word(shelgon);
// 		if (cmd_word)
// 			break ;
// 		(*shelgon)->current = (*shelgon)->current->next;
// 	}
	
// }