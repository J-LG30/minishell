/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:40:09 by julietteleg       #+#    #+#             */
/*   Updated: 2024/04/24 15:49:37 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	while (head && head->type != END && head->next)
	{
		if (cursor->value)
			free(cursor->value);
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
	while (env && env->next)
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
	if (env)
		free(env);
}

void	free_exegg(t_exegg *exe)
{
	int	i;

	i = -1;
	if (!exe)
		return ;
	while (exe->cmdpath && exe->cmdpath[++i])
		free(exe->cmdpath[i]);
	if (exe->path)
		free(exe->path);
	free_env(exe->env);
}