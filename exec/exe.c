/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:30:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/03/22 20:00:57 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_heredoc(t_ast *tree, t_exegg *exe)
{
	int		fd[2];
	char	*res;

	if (tree->left->type == REDIR_DELIMIT)
	{
		pipe(fd);
		while (1)
		{
			res = get_next_line(0);
			if (!res)
				return (-1);
			if (ft_strncmp(av[2], res, ft_strlen(av[2])) == 0 && 
				(ft_strlen(av[2]) == ft_strlen(res) - 1))
				break ;
			ft_putstr_fd(res, fd[1]);
			free(res);
		}
		free(res);
		close(fd[1]);
		return (fd[0]);
	}
}

static void	which_child(t_exegg *ppx, int ac, char **av, char **envp)
{
	ppx->pid1 = fork();
	if (ppx->pid1 < 0)
		ft_error(0, ppx);
	if (ppx->pid1 == 0)
	{
		close(ppx->fd[0]);
		if (ppx->nb_arg == !(ft_strncmp("here_doc", av[1], -1)) + 2)
			fst_child(ppx, av, envp);
		else if (ppx->nb_arg == ac - 2)
			snd_child(ppx, av, envp);
		else
			mid_child(ppx, av, envp);
	}
	else
	{
		if (ppx->nb_arg == !(ft_strncmp("here_doc", av[1], -1)) + 2)
			close(ppx->fd_in);
		else if (ppx->nb_arg == ac - 2)
			close(ppx->fd_out);
		close(ppx->fd[1]);
		ppx->dup_fd[1] = dup2(ppx->fd[0], STDIN_FILENO);
		close(ppx->fd[0]);
	}
}

static void	ft_pipe(t_exegg ppx, int ac, char **av, char **envp)
{
	if (pipe(ppx.fd) == 0)
		which_child(&ppx, ac, av, envp);
	else
	{
		ft_putendl_fd("pipefd is not valid.", 2);
		ft_freedad(&ppx, av);
		exit (1);
	}
}

void	find_redir(t_ast *tree, t_exegg *exe)
{
	while (tree->left)
	{
		if (tree->left->type == REDIR_IN)
		{
			if (exe->fd_in != STDIN_FILENO)
				close(exe->fd_in);
			exe->in_value = tree->left->value;
			exe->fd_in = open(exe->in_value, O_RDONLY);
		}
		else if (tree->left->type == REDIR_DELIMIT)
		{
			if (exe->fd_in != stdin)
				close(exe->fd_in);
			exe->fd_in = ft_heredoc(tree->left->value);
		}
		else if (tree->left->type == REDIR_OUT)
		{
			if (exe->fd_out != stdout)
				close(exe->fd_out);
			exe->out_value = tree->left->value;
			exe->fd_out = open(exe->out_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (tree->left->type == REDIR_APP)
		{
			if (exe->fd_out != stdout)
				close(exe->fd_out);
			exe->out_value = tree->left->value;
			exe->fd_out = open(exe->out_value, O_CREAT | O_APPEND | O_WRONLY, 0644);
		}
		tree->left = tree->left->left;
	}
	if (exe->in_value == STDIN_FILENO)
		exe->fd_in = open(exe->in_value, O_RDONLY);
	if (exe->out_value == STDOUT_FILENO)
		exe->fd_out = open(exe->out_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (exe->fd_in < 0 || exe->fd_out < 0)
		ft_error(1, NULL);
}

int	exeggutor(t_ast	*tree)
{
	t_exegg	exe;

	exe.in_value = STDIN_FILENO;
	exe.out_value = STDOUT_FILENO;
	ft_path(&ppx, envp);
	ft_heredoc(tree, &exe);
	/* while (++ppx.nb_arg < ac - 1)
		ft_pipe(ppx, ac, av, envp); */
	//ft_freedad(&ppx, av);
	return (0);
}
