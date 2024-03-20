/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:36:32 by davda-si          #+#    #+#             */
/*   Updated: 2024/03/18 17:50:30 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*try_cmd(char *cargs, char **cpath)
{
	char	*temp;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	while (cpath[i])
	{
		temp = ft_strjoin(cpath[i], "/");
		cmd = ft_strjoin(temp, cargs);
		free(temp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	fst_child(t_exegg *ppx, char **av, char **envp)
{
	ppx->dup_fd[0] = dup2(ppx->fd[1], STDOUT_FILENO);
	ppx->dup_fd[1] = dup2(ppx->fd_in, STDIN_FILENO);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->fd_in);
	close(ppx->fd_out);
	if (ppx->dup_fd[0] < 0 || ppx->dup_fd[1] < 0)
		ft_error(1, ppx);
	ppx->cargs = ft_split(av[ppx->nb_arg], ' ');
	ppx->cmd = try_cmd(ppx->cargs[0], ppx->cpath);
	if (!ppx->cmd)
	{
		ft_freech(ppx);
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(ppx->cmd, ppx->cargs, envp);
	ft_putendl_fd("Error executing command", 2);
	ft_freech(ppx);
	exit (1);
}

void	snd_child(t_exegg *ppx, char **av, char **envp)
{
	ppx->dup_fd[0] = dup2(ppx->fd_out, STDOUT_FILENO);
	close(ppx->fd[1]);
	close(ppx->fd_out);
	if (ppx->dup_fd[0] < 0)
		ft_error(0, ppx);
	ppx->cargs = ft_split(av[ppx->nb_arg], ' ');
	ppx->cmd = try_cmd(ppx->cargs[0], ppx->cpath);
	if (!ppx->cmd)
	{
		ft_freech(ppx);
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(ppx->cmd, ppx->cargs, envp);
	ft_putendl_fd("Error executing command", 2);
	ft_freech(ppx);
	exit (1);
}

void	mid_child(t_exegg *ppx, char **av, char **envp)
{
	ppx->dup_fd[0] = dup2(ppx->fd[1], STDOUT_FILENO);
	close(ppx->fd[1]);
	close(ppx->fd_out);
	if (ppx->dup_fd[0] < 0)
		ft_error(1, ppx);
	ppx->cargs = ft_split(av[ppx->nb_arg], ' ');
	ppx->cmd = try_cmd(ppx->cargs[0], ppx->cpath);
	if (!ppx->cmd)
	{
		ft_freech(ppx);
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(ppx->cmd, ppx->cargs, envp);
	ft_putendl_fd("Error executing command", 2);
	ft_freech(ppx);
	exit (1);
}
