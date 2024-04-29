/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:30:45 by david             #+#    #+#             */
/*   Updated: 2024/04/29 13:58:17 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	only_redir(t_ast *tree, t_exegg *exe)
{
	t_ast	*temp;

	temp = tree;
	exe->fd_in = STDIN_FILENO;
	exe->fd_out = STDOUT_FILENO;
	if (temp && temp->type == REDIR_IN)
	{
		if (exe->fd_in != STDIN_FILENO)
			close(exe->fd_in);
		exe->in_value = temp->value;
		exe->fd_in = open(exe->in_value, O_RDONLY);
	}
	else if (temp && temp->type == REDIR_OUT)
	{
		exe->out_value = temp->value;
		exe->fd_out = open(exe->out_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (temp && temp->type == REDIR_APP)
	{
		exe->out_value = temp->value;
		exe->fd_out = open(exe->out_value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
}

static void	parent_process(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	if (cmds->prev == NULL && exe->fd_in != STDIN_FILENO)
		close(exe->fd_in);
	else if ((cmds->next == NULL || cmds->next->ref->type != WORD)
		&& exe->fd_out != STDOUT_FILENO)
		close(exe->fd_out);
	close(exe->fd[1]);
	if (exe->last_fd != STDIN_FILENO)
		close(exe->last_fd);
	if (cmds->next)
		exe->last_fd = exe->fd[0];
	else
		close(exe->fd[0]);
}

void	which_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	exe->pid1 = fork();
	if (exe->pid1 < 0)
	{
		ft_putendl_fd("dork\n", 2);
		ft_error(0, exe);
	}
	if (exe->pid1 == 0)
	{
		close(exe->fd[0]);
		if (cmds->prev == NULL)
			fst_child(tree, exe, cmds);
		else if (cmds->next == NULL || cmds->next->ref->type != WORD)
			lst_child(tree, exe, cmds);
		else
			mid_child(tree, exe, cmds);
	}
	else
		parent_process(tree, exe, cmds);
}

char	*try_cmd(char *cargs, char **cpath)
{
	char	*temp;
	char	*com;
	int		i;

	i = 0;
	com = NULL;
	if (!cpath)
		return (NULL);
	while (cpath[i])
	{
		temp = ft_strjoin(cpath[i], "/");
		com = ft_strjoin(temp, cargs);
		free(temp);
		if (access(com, F_OK) == 0)
			return (com);
		free(com);
		i++;
	}
	return (NULL);
}

int	pipe_it(t_ast *tree, t_shelgon *shelgon, t_branch *cmds, t_exegg *exe)
{
	int i;

	i = 0;
	while (cmds)
	{
		if (cmds->ref->type == WORD)
		{
			ft_pipe(tree, exe, cmds);
			i++;
		}
		cmds = cmds->next;
	}
	return (i);
}
