/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:22:13 by david             #+#    #+#             */
/*   Updated: 2025/01/14 13:24:02 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	pr_nod(t_ast *temp, t_branch *cur, t_branch *last, t_branch **cmds)
{
	cur = node_cmd(temp);
	if (!cur)
		return (0);
	if (!(*cmds))
	{
		*cmds = cur;
		cur->prev = NULL;
	}
	else
	{
		last = msh_lstlast(*cmds);
		last->next = cur;
		cur->prev = last;
	}
	return (1);
}

//ft_memset(cur, 0, 0); <= took this out for lines, dont think it was necessary
int	pr_her(t_ast *temp, t_branch *cur, t_branch *last, t_branch **cmds)
{
	cur = ft_calloc(1, sizeof(t_branch));
	if (!cur)
		return (0);
	set_heredoc_handler();
	cur->pipe[0] = ft_heredoc(temp, temp->shell);
	set_child_handler();
	if (g_sig == 1)
	{
		close(cur->pipe[0]);
		free(cur);
		return (-1);
	}
	cur->ref = temp;
	if (!(*cmds))
	{
		*cmds = cur;
		cur->prev = NULL;
	}
	else
	{
		last = msh_lstlast(*cmds);
		last->next = cur;
		cur->prev = last;
	}
	return (1);
}

static int	c_help(t_ast *temp, t_branch *cur, t_branch *last, t_branch **cmds)
{
	if (temp && temp->type != PIPE && temp->type != WORD
		&& temp->type != REDIR_DELIMIT)
	{
		cur = ft_calloc(1, sizeof(t_branch));
		if (!cur)
			return (0);
		ft_memset(cur, 0, 0);
		cur->ref = temp;
		if (!(*cmds))
		{
			*cmds = cur;
			cur->prev = NULL;
		}
		else
		{
			last = msh_lstlast(*cmds);
			last->next = cur;
			cur->prev = last;
		}
	}
	if (cur)
		cur->next = NULL;
	return (1);
}

static void	looper(t_ast *temp, t_branch **cmds, t_exegg *exe, t_ast *tree)
{
	temp = tree;
	if (temp && temp->type == PIPE)
		get_cmd(temp->right, cmds, exe);
}

int	get_cmd(t_ast *tree, t_branch **cmds, t_exegg *exe)
{
	t_ast		*temp;
	t_branch	*cur;
	t_branch	*last;
	int			ret;

	temp = tree;
	cur = NULL;
	last = NULL;
	while (temp)
	{
		if (temp && temp->type == WORD)
		{
			if (pr_nod(temp, cur, last, cmds) == 0)
				return (0);
			exe->no_cmds = 0;
		}
		ret = redir_del(temp, cur, last, cmds);
		if (ret != 1)
			return (ret);
		if (c_help(temp, cur, last, cmds) == 0)
			return (0);
		temp = temp->left;
	}
	looper(temp, cmds, exe, tree);
	return (exe->no_cmds);
}
