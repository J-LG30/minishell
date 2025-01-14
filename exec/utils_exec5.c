/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:18:58 by davda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:27:29 by jle-goff         ###   ########.fr       */
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

static void	mid_prep(t_exegg *exe, t_branch *cmds)
{
	exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	close(exe->fd_in);
	close(exe->fd_out);
	if (exe->dup_fd[0] < 0)
		ft_error(1, cmds, exe);
	if (cmds->full_cmd[0][0] == '/'
		|| (cmds->full_cmd[0][0] == '.' && cmds->full_cmd[0][1] == '/'))
		execve(cmds->full_cmd[0], cmds->full_cmd, exe->pkcenter->envr);
}

void	mid_child(t_exegg *exe, t_branch *cmds)
{
	find_redir(cmds->ref, exe, cmds);
	mid_prep(exe, cmds);
	if (cmds->ref && cmds->ref->type == WORD && !(is_btin(cmds->full_cmd[0])))
	{
		cmds->cmd = try_cmd(cmds->full_cmd[0], exe->cmdpath);
		if (!cmds->cmd)
		{
			ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: ", 2);
			ft_putstr_fd(cmds->full_cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			free_all(exe->pkcenter, exe, WRONG_CMD);
			exit (127);
		}
	}
	if (is_btin(cmds->full_cmd[0]))
		run_btin(exe, cmds, 0);
	else
	{
		execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
		ft_putendl_fd("Error executing command", 2);
	}
	exit (1);
}
