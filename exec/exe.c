/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:30:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/27 13:51:00 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	only_redir(t_ast *tree, t_exegg *exe)
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

int	ft_heredoc(t_ast *tree)
{
	int		fd[2];
	char	*res;
	t_ast	*temp;

	temp = tree;
	set_prompt_handler();
	if (temp && temp->type == REDIR_DELIMIT)
	{
		pipe(fd);
		while (1)
		{
			res = readline("> ");
			if (!res)
			{
				
				ft_putendl_fd("(╯°□ °)╯︵ ┻━┻: warning: here-document at line 1 delimited by end-of-file", 2);
				rl_on_new_line();
				return (-1);
			}
			if (ft_strncmp(temp->value, res, ft_strlen(temp->value)) == 0 && 
				(ft_strlen(temp->value) == ft_strlen(res)))
				break ;
			ft_putstr_fd(res, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			free(res);
		}
		free(res);
		close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

static void	which_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
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
		if (cmds->prev == NULL && exe->fd_in != STDIN_FILENO)
			close(exe->fd_in);
		else if ((cmds->next == NULL || cmds->next->ref->type != WORD) && exe->fd_out != STDOUT_FILENO)
			close(exe->fd_out);
		close(exe->fd[1]);
		if (exe->last_fd != STDIN_FILENO)
			close(exe->last_fd);
		if (cmds->next)
			exe->last_fd = exe->fd[0];
		else
			close(exe->fd[0]);
}

static void	ft_pipe(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	int	saved_fileout[2];
	if (is_btin(cmds->full_cmd[0]) && (!cmds->next || cmds->next->ref->type != WORD) && (!cmds->prev))
	{
		saved_fileout[0] = STDIN_FILENO;
		saved_fileout[1] = STDOUT_FILENO;
		find_redir(tree, exe, cmds);
		if (((!cmds->next || cmds->next->ref->type != WORD) && !(tree && (tree->type == PIPE)) && exe->fd_out == saved_fileout[1]))
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
		else if ((cmds->next == NULL || (cmds->next && cmds->next->ref->type != WORD)) && exe->fd_out != STDOUT_FILENO)
			close(exe->fd_out);
		if (exe->last_fd != STDIN_FILENO)
			close(exe->last_fd);
		dup2(exe->fd_out, saved_fileout[0]);
		dup2(exe->fd_in, saved_fileout[1]);
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
		else if (temp && temp->type == REDIR_DELIMIT)
		{
			while (com)
			{
				if (com->ref && com->ref->type == REDIR_DELIMIT)
					exe->fd_in = com->pipe[0];
				com = com->next;
			}
		}
		temp = temp->left;
	}
	if (exe->fd_in == STDIN_FILENO)
		exe->fd_in = exe->last_fd;
	if (exe->fd_out == STDOUT_FILENO)
		exe->fd_out = exe->fd[1];
}

int	exeggutor(t_ast *tree, t_shelgon *shelgon, t_env *env)
{
	t_exegg		*exe;
	t_branch	*cmds;
	int			i;
	int s;
	
	exe = malloc(sizeof(t_exegg) * 1);
	if (!exe)
		return (1);
	shelgon->exe = exe;
	s = 0;
	exe->fd_in = STDIN_FILENO;
	exe->fd_out = STDOUT_FILENO;
	exe->dup_fd[0] = STDIN_FILENO;
	exe->dup_fd[1] = STDOUT_FILENO;
	exe->fd[0] = STDIN_FILENO;
	exe->fd[1] = STDOUT_FILENO;
	exe->redir = 'n';
	exe->pkcenter = shelgon;
	cmds = NULL;
	exe->last_fd = 0;
	if (get_cmd(tree, &cmds, exe))
	{
		only_redir(tree, exe);
		return (1);
	}
	exe->cmd = cmds;
	ft_path(exe, env);
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
	free_exegg(exe);
	return (0);
}
