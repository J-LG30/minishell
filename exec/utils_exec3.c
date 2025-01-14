/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:56:46 by david             #+#    #+#             */
/*   Updated: 2025/01/14 13:33:24 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_heredoc(t_ast *tree, t_shelgon *shelgon)
{
	int		fd[2];
	char	*res;
	t_ast	*temp;
	int		ret;

	res = NULL;
	temp = tree;
	if (temp && temp->type == REDIR_DELIMIT)
	{
		pipe(fd);
		ret = here_loop(res, fd, temp, shelgon);
		if (ret != -4)
			return (ret);
		close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

static void	last_red(t_exegg *exe)
{
	if (exe->fd_in == STDIN_FILENO)
		exe->fd_in = exe->last_fd;
	if (exe->fd_out == STDOUT_FILENO)
		exe->fd_out = exe->fd[1];
}

static void	do_red(t_ast *temp, t_exegg *exe, int fl)
{
	if (temp && fl == 0 && treat_in(temp, exe))
		return ;
	else if (temp && fl == 1)
		take_out(exe, temp);
	else if (temp && fl == 2)
	{
		if (exe->fd_out != STDOUT_FILENO)
			close(exe->fd_out);
		exe->out_value = temp->value;
		exe->fd_out = open(exe->out_value, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (exe->fd_out < 0)
			fd_message(temp, exe);
	}
	else if (fl == 3)
		last_red(exe);
}

static void	deal_doc(t_exegg *exe, t_branch *com)
{
	while (com)
	{
		if (com->ref && com->ref->type == REDIR_DELIMIT)
		{
			if (exe->fd_in > 2)
				close(exe->fd_in);
			exe->fd_in = dup(com->pipe[0]);
		}
		com = com->next;
	}
}

void	find_redir(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	t_ast		*temp;
	t_branch	*com;

	temp = tree;
	com = cmds;
	exe->fd_in = STDIN_FILENO;
	exe->fd_out = STDOUT_FILENO;
	exe->err = 0;
	while (temp)
	{
		if (exe->err)
			return ;
		if (temp && temp->type == REDIR_IN)
			do_red(temp, exe, 0);
		else if (temp && temp->type == REDIR_OUT)
			do_red(temp, exe, 1);
		else if (temp && temp->type == REDIR_APP)
			do_red(temp, exe, 2);
		else if (temp && temp->type == REDIR_DELIMIT)
			deal_doc(exe, com);
		temp = temp->left;
	}
	do_red(temp, exe, 3);
}
