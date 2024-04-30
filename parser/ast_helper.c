/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:25 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/30 14:52:43 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*new_node_init(void)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast) * 1);
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->type = -1;
	new->value = NULL;
	new->heredoc = 0;
	return (new);
}

t_ast	*new_pipe_node(t_token *temp)
{
	t_ast	*new;

	new = new_node_init();
	if (!new)
		return (NULL);
	new->type = PIPE;
	return (new);
}

//idk if i need to memcpy the string to the node or if 
//just pointing to the token memory works tbc
t_ast	*new_word_node(t_token *token)
{
	t_ast	*new;

	new = new_node_init();
	if (!new)
		return (NULL);
	new->type = token->type;
	new->value = token->value;
	return (new);
}

t_ast	*new_redir_node(t_token *token)
{
	t_ast	*new;
	int		i;
	int		flag;

	new = new_node_init();
	if (!new)
		return (NULL);
	new->type = token->type;
	i = 0;
	flag = 0;
	if (token->type == REDIR_DELIMIT)
	{
		while (token->next->copy[i])
		{
			if (token->next->copy[i] == '\'' || token->next->copy[i] == '"')
				flag = 1;
			i++;
		}
		if (flag == 0)
			new->heredoc = 1;
	}
	new->value = token->next->value;
	return (new);
}

t_ast	*new_end_node(void)
{
	t_ast	*new;

	if (!new)
		return (NULL);
	new->type = END;
	return (new);
}
