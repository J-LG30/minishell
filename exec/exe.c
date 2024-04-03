/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:30:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/03 21:27:08 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_heredoc(t_ast *tree)
{
	int		fd[2];
	char	*res;
	t_ast	*temp;

	temp = tree;
	if (temp->type == REDIR_DELIMIT)
	{
		pipe(fd);
		while (1)
		{
			res = readline("> ");
			if (!res)
				return (-1);
			if (ft_strncmp(temp->value, res, ft_strlen(temp->value)) == 0 && 
				(ft_strlen(temp->value) == ft_strlen(res) - 1))
				break ;
			ft_putstr_fd(res, fd[1]);
			free(res);
		}
		free(res);
		my_close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

static void	which_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	exe->pid1 = fork();
	if (exe->pid1 < 0)
		ft_error(0, exe);
	if (exe->pid1 == 0)
	{
		my_close(exe->fd[0]);
		if (cmds->prev == NULL)
			fst_child(tree, exe, cmds);
		else if (cmds->next == NULL)
			lst_child(tree, exe, cmds);
		else

			mid_child(tree, exe, cmds);
	}
	else
		if (cmds->prev == NULL && exe->fd_in != STDIN_FILENO)
			my_close(exe->fd_in);
		else if (cmds->next == NULL && exe->fd_out != STDOUT_FILENO)
			my_close(exe->fd_out);
		my_close(exe->fd[1]);
		if (exe->last_fd != STDIN_FILENO)
			my_close(exe->last_fd);
		exe->last_fd = exe->fd[0];
}

static void	ft_pipe(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	if (pipe(exe->fd) == 0)
		which_child(tree, exe, cmds);
	else
	{
		ft_putendl_fd("pipefd is not valid.", 2);
		//ft_freedad(&exe);
		exit (1);
	}
}

void	find_redir(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	t_ast	*temp;

	temp = tree;
	while (temp)
	{
		if (temp->left && temp->left->type == REDIR_IN)
		{
			if (exe->fd_in != STDIN_FILENO)
				close(exe->fd_in);
			exe->in_value = temp->left->value;
			exe->fd_in = open(exe->in_value, O_RDONLY);
		}
		else if (temp->left && temp->left->type == REDIR_DELIMIT)
			exe->fd_in = exe->cmd->pipe[0];
		else if (temp->left && temp->left->type == REDIR_OUT)
		{
			exe->out_value = temp->left->value;
			exe->fd_out = open(exe->out_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (temp->left && temp->left->type == REDIR_APP)
		{
			exe->out_value = temp->left->value;
			exe->fd_out = open(exe->out_value, O_CREAT | O_APPEND | O_WRONLY, 0644);
		}
		temp = temp->left;
	}
	if (exe->fd_in == STDIN_FILENO)
		exe->fd_in = exe->last_fd;
	if (exe->fd_out == STDOUT_FILENO)
		exe->fd_out = exe->fd[1];
}

int	exeggutor(t_ast *tree, t_shelgon *shelgon)
{
	t_exegg		exe;
	t_branch	*cmds;
	int			i;

	exe.fd_in = STDIN_FILENO;
	exe.fd_out = STDOUT_FILENO;
	exe.dup_fd[0] = STDIN_FILENO;
	exe.dup_fd[1] = STDOUT_FILENO; 
	exe.redir = 'n';
	exe.pkcenter = shelgon;
	cmds = NULL;
	get_cmd(tree, &cmds);
	ft_path(&exe);
	i = 0;
	exe.last_fd = 0;
	while (cmds)
	{
		ft_pipe(tree, &exe, cmds);
		cmds = cmds->next;
		i++;
	}
	while (--i >= 0)
		wait(NULL);
	return (0);
}
