/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:40:09 by julietteleg       #+#    #+#             */
/*   Updated: 2024/04/25 15:42:56 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_env(t_env *env);

void	free_shelgon(t_shelgon *sh)
{
	int	i;

	i = 0;
	while (sh->envr && sh->envr[i])
	{
		free(sh->envr[i]);
		i++;
	}
	if (sh->envr)
		free(sh->envr);
	free_env(sh->env);
	free(sh);
}
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
		if (cursor->copy)
			free(cursor->copy);
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

void	free_branch(t_branch *branch)
{
	t_branch	*cursor;
	int			i;

	if (!branch)
		return ;
	cursor = branch;
	while (branch && branch->next)
	{
		i = 0;
		if (cursor->cmd)
			free(cursor->cmd);
		while (cursor->args && cursor->args[i])
		{
			free(cursor->args[i]);
			i++;
		}
		if (cursor->args)
			free(cursor->args);
		i = 0;
		while (cursor->full_cmd && cursor->full_cmd[i])
		{
			free(cursor->full_cmd[i]);
			i++;
		}
		branch = branch->next;
		if (cursor)
			free(cursor);
		cursor = branch;
	}
	if (branch)
		free(branch);
}
void	free_exegg(t_exegg *exe)
{
	int	i;

	i = 0;
	if (!exe)
		return ;
	while (exe->cmdpath && exe->cmdpath[i])
	{
		free(exe->cmdpath[i]);
		i++;
	}
	//free_branch(exe->cmd);
}