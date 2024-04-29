/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:22:13 by david             #+#    #+#             */
/*   Updated: 2024/04/28 23:40:35 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_cmds(t_ast *temp)
{
	int	j;

	j = 1;
	while (temp->right && temp->right->type == WORD)
	{
		j++;
		temp = temp->right;
	}
	return (j);
}

static int	save_fullcmd(t_ast *temp, t_branch *new)
{
	int	i;

	i = 0;
	if (new->cmd)
		new->full_cmd[0] = new->cmd;
	new->ref = temp;
	while (temp->right && temp->right->type == WORD)
	{
		i++;
		new->full_cmd[i] = temp->right->value;
		temp = temp->right;
	}
	new->full_cmd[i + 1] = NULL;
	new->pipe[0] = 0;
	return (i);
}

t_branch	*node_cmd(t_ast *tree)
{
	t_branch	*new;
	t_ast		*temp;
	int			i;
	int			j;

	i = 0;
	j = 1;
	temp = tree;
	new = ft_calloc(1, sizeof(t_branch));
	if (!new)
		return (NULL);
	if (temp->type == WORD)
	{
		new->cmd = temp->value;
		j = count_cmds(temp);
		new->full_cmd = (char **)malloc(sizeof(char *) * (j + 1));
		if (!new->full_cmd)
			return (NULL);
		temp = tree;
		i = save_fullcmd(temp, new);
	}
	new->full_cmd[i + 1] = NULL;
	return (new);
}

int	get_cmd(t_ast *tree, t_branch **cmds, t_exegg *exe)
{
	t_ast		*temp;
	t_branch	*cur;
	t_branch	*last;
	int			no_cmds;
	static int	i = 0;

	temp = tree;
	no_cmds = 1;
	cur = NULL;
	while (temp)
	{
		if (temp && temp->type == WORD)
		{
			cur = node_cmd(temp);
			if (!cur)
				return (0);
			if(!(*cmds))
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
			i++;
			no_cmds = 0;
		}
		else if (temp && temp->type == REDIR_DELIMIT)
		{
			cur = ft_calloc(1, sizeof(t_branch));
			if (!cur)
				return (0);
			ft_memset(cur, 0, 0);
			cur->pipe[0] = ft_heredoc(temp);
			set_child_handler();
			cur->ref = temp;
			if(!(*cmds))
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
		temp = temp->left;
	}
	if (temp && temp->type != PIPE && temp->type != WORD && temp->type != REDIR_DELIMIT)
	{
		cur = ft_calloc(1, sizeof(t_branch));
		if (!cur)
			return (0);
		ft_memset(cur, 0, 0);
		cur->ref = temp;
		if(!(*cmds))
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
	temp = tree;
	if (temp && temp->type == PIPE)
		get_cmd(temp->right, cmds, exe);
	return (no_cmds);
}
