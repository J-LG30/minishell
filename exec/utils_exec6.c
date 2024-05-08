/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:22:45 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/07 19:46:16 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_loop(char *res, int *fd, t_ast *temp, t_shelgon *shelgon)
{
	int	std_in;

	std_in = dup(STDIN_FILENO);
	while (1)
	{
		res = readline("> ");
		if (g_sig == 1)
			return (here_help(std_in, res, fd));
		if (!res)
			return (err_heredoc(fd, std_in, res, shelgon));
		if (ft_strncmp(temp->value, res, ft_strlen(temp->value)) == 0
			&& (ft_strlen(temp->value) == ft_strlen(res)))
			break ;
		if (temp->heredoc)
			res = check_heredoc(res, shelgon);
		ft_putendl_fd(res, fd[1]);
		free(res);
	}
	close(std_in);
	return (-4);
}

int	err_heredoc(int *fd, int std_in, char *res, t_shelgon *shelgon)
{
	shelgon->status = 0;
	g_sig = 2;
	ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: warning", 2);
	ft_putendl_fd(": here-document delimited by end-of-file", 2);
	rl_on_new_line();
	if (std_in > 2)
		close(std_in);
	if (fd[1] > 2)
		close(fd[1]);
	return (fd[0]);
}

void	close_fds(t_exegg *exe)
{
	close(exe->fd_in);
	close(exe->fd_out);
	close(exe->dup_fd[0]);
	close(exe->dup_fd[1]);
	exe->fd_in = dup2(exe->saved_file[0], STDIN_FILENO);
	exe->fd_out = dup2(exe->saved_file[1], STDOUT_FILENO);
	close(exe->saved_file[1]);
	close(exe->saved_file[0]);
}

int	treat_in(t_ast *temp, t_exegg *exe, t_branch *cmds)
{
	int	fd;

	exe->in_value = temp->value;
	if (exe->btin && ft_strcmp(exe->in_value, exe->out_value) == 0 && exe->err)
	{
		exe->err = 1;
		return (1);
	}
	fd = open(exe->in_value, O_RDONLY);
	if (exe->fd_in != STDIN_FILENO)
		close(exe->fd_in);
	exe->fd_in = fd;
	if ((exe->fd_in < 0 || exe->err))
	{
		fd_message(temp, exe);
		return (1);
	}
	return (0);
}

void	treat_only(t_exegg *exe, t_ast *temp, int fl)
{
	if (fl == 1)
	{
		exe->out_value = temp->value;
		exe->fd_out = open(exe->out_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (exe->fd_out < 0)
			fd_message(temp, exe);
	}
	else if (fl == 2)
	{
		exe->out_value = temp->value;
		exe->fd_out = open(exe->out_value, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (exe->fd_out < 0)
			fd_message(temp, exe);
	}
}
