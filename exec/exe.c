/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:30:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/28 23:15:06 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	built_red(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	int	saved_file[2];

	saved_file[0] = STDIN_FILENO;
	saved_file[1] = STDOUT_FILENO;
	find_redir(tree, exe, cmds);
	if (((!cmds->next || cmds->next->ref->type != WORD)
			&& !(tree && (tree->type == PIPE)) && exe->fd_out == saved_file[1]))
		exe->fd_out = STDOUT_FILENO;
	if (exe->fd_in != STDIN_FILENO)
		exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	if (exe->fd_out != STDOUT_FILENO)
		exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	if (exe->fd_in != STDIN_FILENO)
		close(exe->fd_in);
	if (exe->fd_out != STDOUT_FILENO)
		close(exe->fd_out);
	run_btin(tree, exe, cmds, 1);
	if (cmds->prev == NULL && exe->fd_in != STDIN_FILENO)
		close(exe->fd_in);
	if ((cmds->next == NULL || (cmds->next && cmds->next->ref->type != WORD))
		&& exe->fd_out != STDOUT_FILENO)
		close(exe->fd_out);
	dup2(exe->fd_out, saved_file[0]);
	dup2(exe->fd_in, saved_file[1]);
}

static void	ft_pipe(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	if (is_btin(cmds->full_cmd[0])
		&& (!cmds->next || cmds->next->ref->type != WORD) && (!cmds->prev))
	{
		built_red(tree, exe, cmds);
		if (exe->last_fd != STDIN_FILENO)
			close(exe->last_fd);
		return ;
	}
	else if (pipe(exe->fd) == 0)
		which_child(tree, exe, cmds);
	else
	{
		ft_putendl_fd("pipefd is not valid.", 2);
		exit (1);
	}
}

static void	save_exe(t_shelgon *shelgon, t_exegg *exe)
{
	shelgon->exe = exe;
	exe->fd_in = STDIN_FILENO;
	exe->fd_out = STDOUT_FILENO;
	exe->dup_fd[0] = STDIN_FILENO;
	exe->dup_fd[1] = STDOUT_FILENO;
	exe->fd[0] = STDIN_FILENO;
	exe->fd[1] = STDOUT_FILENO;
	exe->redir = 'n';
	exe->pkcenter = shelgon;
	exe->last_fd = 0;
}

static void	exeg(t_ast *tree, t_shelgon *shelgon, t_branch *cmds, t_exegg *exe)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (cmds)
	{
		if (cmds->ref->type == WORD)
		{
			ft_pipe(tree, exe, cmds);
			i++;
		}
		cmds = cmds->next;
	}
	while (--i >= 0)
		wait(&s);
	if (WIFEXITED(s))
		shelgon->status = WEXITSTATUS(s);
	else if (WIFSIGNALED(s))
	{
		if (WTERMSIG(s) == SIGINT)
			shelgon->status = 130;
		else if (WTERMSIG(s) == SIGQUIT)
			shelgon->status = 131;
	}
}

int	exeggutor(t_ast *tree, t_shelgon *shelgon, t_env *env)
{
	t_exegg		*exe;
	t_branch	*cmds;
	int			i;
	int			s;

	s = 0;
	cmds = NULL;
	exe = malloc(sizeof(t_exegg) * 1);
	if (!exe)
		return (1);
	save_exe(shelgon, exe);
	if (get_cmd(tree, &cmds, exe))
	{
		only_redir(tree, exe);
		return (1);
	}
	exe->cmd = cmds;
	ft_path(exe, env);
	exeg(tree, shelgon, cmds, exe);
	free_exegg(exe);
	return (0);
}
