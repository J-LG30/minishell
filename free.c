/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:40:09 by julietteleg       #+#    #+#             */
/*   Updated: 2024/05/02 21:35:54 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	free_env(t_env *env);

//recursively free ast. probably will have to update it
void	free_ast(t_ast	*tree)
{
	t_ast	*cursor;
	t_ast	*left;
	t_ast	*right;

	cursor = tree;
	if (cursor)
	{
		left = cursor->left;
		right = cursor->right;
		free(cursor);
		free_ast(left);
		free_ast(right);
	}
	return ;
}

void	free_tokens(t_token *head)
{
	t_token	*cursor;

	cursor = head;
	if (!head)
		return ;
	while (head && head->type != END)
	{
		if (head->value)
			free(head->value);
		if (head->copy)
			free(head->copy);
		head = head->next;
		if (cursor)
			free(cursor);
		cursor = head;
	}
	if (head)
		free(head);
}

void	free_env(t_env *env)
{
	t_env	*cursor;

	if (!env)
		return ;
	cursor = env;
	while (env)
	{
		if (cursor->vr)
			free(cursor->vr);
		if (cursor->cpy)
			free(cursor->cpy);
		env = env->next;
		if (cursor)
			free(cursor);
		cursor = env;
	}
}

void	free_shelgon(t_shelgon *sh)
{
	int	i;

	i = 0;
	if (!sh)
		return ;
	if (sh->list_token)
		free_tokens(sh->list_token);
	if (sh->tree)
		free_ast(sh->tree);
	while (sh->envr && sh->envr[i] && sh->free)
	{
		if (sh->envr[i])
			free(sh->envr[i]);
		i++;
	}
	if (!sh->free)
		free(sh->envr[0]);
	if (sh->envr)
		free(sh->envr);
	if (sh->env)
		free_env(sh->env);
	if (sh)
		free(sh);
}

void	free_all(t_shelgon *shelgon, t_exegg *exe, int flag)
{
	if (flag == WRONG_CMD || flag == BTIN)
		free_exegg(exe);
	free_shelgon(shelgon);
}
