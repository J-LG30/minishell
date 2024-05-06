/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:30:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/06 18:57:04 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	built_red(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	exe->saved_file[0] = dup(STDIN_FILENO);
	exe->saved_file[1] = dup(STDOUT_FILENO);
	find_redir(tree, exe, cmds);
	if (exe->err)
	{
		if (exe->fd_out != STDOUT_FILENO && exe->fd_out > 2)
			close(exe->fd_out);
		if (exe->fd_in != STDIN_FILENO && exe->fd_in > 2)
			close(exe->fd_in);
		close(exe->saved_file[0]);
		close(exe->saved_file[1]);
		return ;
	}
	if (((!cmds->next || cmds->next->ref->type != WORD)
			&& !(tree && (tree->type == PIPE))
			&& exe->fd_out == exe->saved_file[1]))
		exe->fd_out = STDOUT_FILENO;
	if (exe->fd_in != STDIN_FILENO)
		exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	if (exe->fd_in != STDIN_FILENO && exe->fd_in > 2)
		close(exe->fd_in);
	if (exe->fd_out != STDOUT_FILENO)
		exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	run_btin(tree, exe, cmds, 1);
	close_fds(exe);
}

void	ft_pipe(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	if (is_btin(cmds->full_cmd[0])
		&& (!cmds->next || cmds->next->ref->type != WORD) && !cmds->prev)
	{
		exe->btin = 1;
		built_red(tree, exe, cmds);
		if (exe->last_fd != STDIN_FILENO && exe->last_fd > 2)
			close(exe->last_fd);
		return ;
	}
	else if (cmds->ref->type == WORD && exe->err == 0)
	{
		if (pipe(exe->fd) == 0 && cmds->ref->type == WORD)
			which_child(tree, exe, cmds);
	}
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
	exe->saved_file[0] = STDIN_FILENO;
	exe->saved_file[1] = STDOUT_FILENO;
	exe->redir = 'n';
	exe->pkcenter = shelgon;
	exe->last_fd = 0;
	exe->cmdpath = NULL;
	exe->no_cmds = 1;
	exe->in_value = NULL;
	exe->out_value = NULL;
	exe->pid1 = 0;
	exe->btin = 0;
	exe->err = 0;
}

static void	exeg(t_ast *tree, t_shelgon *shelgon, t_branch *cmds, t_exegg *exe)
{
	int	i;
	int	s;
	int	flag;

	s = 0;
	flag = 0;
	s = 0;
	i = pipe_it(tree, shelgon, cmds, exe);
	if (exe->pid1 && exe->btin == 0)
		waitpid(exe->pid1, &s, 0);
	while (--i >= 0)
		wait(NULL);
	if (exe->btin)
		flag = 1;
	if (WIFEXITED(s) != 0 && flag == 0)
		shelgon->status = WEXITSTATUS(s);
	else if (WIFSIGNALED(s) && flag == 0)
	{
		if (WTERMSIG(s) == SIGINT)
			shelgon->status = 130;
		else if (WTERMSIG(s) == SIGQUIT)
			shelgon->status = 131;
		ft_putchar_fd('\n', 1);
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
	i = get_cmd(tree, &cmds, exe);
	exe->cmd = cmds;
	if (i || i == -1)
	{
		if (i)
			only_redir(tree, exe);
		free_exegg(exe);
		return (1);
	}
	ft_path(exe, env);
	exeg(tree, shelgon, cmds, exe);
	free_exegg(exe);
	return (0);
}
