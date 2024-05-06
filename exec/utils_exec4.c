/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:30:45 by david             #+#    #+#             */
/*   Updated: 2024/05/06 17:58:37 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	only_redir(t_ast *tree, t_exegg *exe)
{
	t_ast	*temp;

	temp = tree;
	exe->fd_in = STDIN_FILENO;
	exe->fd_out = STDOUT_FILENO;
	while (temp)
	{
		if (temp && temp->type == REDIR_IN)
		{
			exe->in_value = temp->value;
			exe->fd_in = open(exe->in_value, O_RDONLY);
		}
		else if (temp && temp->type == REDIR_OUT)
			treat_only(exe, temp, 1);
		else if (temp && temp->type == REDIR_APP)
			treat_only(exe, temp, 2);
		if (exe->fd_in != STDIN_FILENO && exe->fd_in > 2)
			close(exe->fd_in);
		if (exe->fd_out != STDOUT_FILENO && exe->fd_out > 2)
			close(exe->fd_out);
		temp = temp->left;
	}
}

static void	parent_process(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	if (cmds->prev == NULL && exe->fd_in != STDIN_FILENO && exe->fd_in > 2)
		close(exe->fd_in);
	else if ((cmds->next == NULL || cmds->next->ref->type != WORD)
		&& exe->fd_out != STDOUT_FILENO && exe->fd_out > 2)
		close(exe->fd_out);
	if (exe->fd[1] > 2)
		close(exe->fd[1]);
	if (exe->last_fd != STDIN_FILENO && exe->last_fd > 2)
		close(exe->last_fd);
	if (cmds->next)
		exe->last_fd = exe->fd[0];
	else
	{
		if (exe->fd[0] > 2)
			close(exe->fd[0]);
	}
	if (cmds->pipe[0] > 2)
		close(cmds->pipe[0]);
}

void	which_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	exe->pid1 = fork();
	if (exe->pid1 < 0)
		ft_error(0, cmds, exe);
	if (exe->pid1 == 0)
	{
		if (exe->fd[0] > 2)
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
	if (!cpath || !cargs || !cargs[i] || (cargs[0] == '.' && cargs[1] == '.'))
		return (NULL);
	if (cargs[ft_strlen(cargs) - 1] == '.'
		|| cargs[ft_strlen(cargs) - 1] == '/')
		return (NULL);
	while (cpath[i])
	{
		temp = ft_strjoin(cpath[i], "/");
		if (!temp)
			return (NULL);
		com = ft_strjoin(temp, cargs);
		free(temp);
		if (access(com, X_OK) == 0)
			return (com);
		free(com);
		i++;
	}
	return (NULL);
}

int	pipe_it(t_ast *tree, t_shelgon *shelgon, t_branch *cmds, t_exegg *exe)
{
	int	i;

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
