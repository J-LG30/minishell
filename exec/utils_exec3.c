/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:56:46 by david             #+#    #+#             */
/*   Updated: 2024/04/30 14:54:10 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	err_heredoc(int *fd)
{
	ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: warning", 2);
	ft_putendl_fd(": here-document delimited by end-of-file", 2);
	rl_on_new_line();
	close(fd[1]);
	return (fd[0]);
}

int	ft_heredoc(t_ast *tree, t_shelgon *shelgon)
{
	int		fd[2];
	char	*res;
	t_ast	*temp;
	int		std_in;

	std_in = dup(STDIN_FILENO);
	temp = tree;
	if (temp && temp->type == REDIR_DELIMIT)
	{
		pipe(fd);
		while (1)
		{
			res = readline("> ");
			if (temp->heredoc)
				res = check_heredoc(res, shelgon);
			if (g_sig == 1)
			{
				dup2(std_in, STDIN_FILENO);
				return (-2);
			}
			if (!res)
				return (err_heredoc(fd));
			if (ft_strncmp(temp->value, res, ft_strlen(temp->value)) == 0
				&& (ft_strlen(temp->value) == ft_strlen(res)))
				break ;
			ft_putendl_fd(res, fd[1]);
			free(res);
		}
		free(res);
		close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

static void	do_red(t_ast *temp, t_exegg *exe, t_branch *cmds, int fl)
{
	if (temp && fl == 0)
	{
		if (exe->fd_in != STDIN_FILENO)
			close(exe->fd_in);
		exe->in_value = temp->value;
		exe->fd_in = open(exe->in_value, O_RDONLY);
	}
	else if (temp && fl == 1)
	{
		exe->out_value = temp->value;
		exe->fd_out = open(exe->out_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (temp && fl == 2)
	{
		exe->out_value = temp->value;
		exe->fd_out = open(exe->out_value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	else if (fl == 3)
	{
		if (exe->fd_in == STDIN_FILENO)
			exe->fd_in = exe->last_fd;
		if (exe->fd_out == STDOUT_FILENO)
			exe->fd_out = exe->fd[1];
	}
}

static void	deal_doc(t_exegg *exe, t_branch *com)
{
	while (com)
	{
		if (com->ref && com->ref->type == REDIR_DELIMIT)
			exe->fd_in = com->pipe[0];
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
	while (temp)
	{
		if (temp && temp->type == REDIR_IN)
			do_red(temp, exe, cmds, 0);
		else if (temp && temp->type == REDIR_OUT)
			do_red(temp, exe, cmds, 1);
		else if (temp && temp->type == REDIR_APP)
			do_red(temp, exe, cmds, 2);
		else if (temp && temp->type == REDIR_DELIMIT)
			deal_doc(exe, com);
		temp = temp->left;
	}
	do_red(temp, exe, cmds, 3);
}