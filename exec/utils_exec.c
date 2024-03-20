/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:54 by davda-si          #+#    #+#             */
/*   Updated: 2024/03/18 15:35:40 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(char **envp)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			res = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (res == NULL)
	{
		ft_putendl_fd("Path not found", 2);
		return (NULL);
	}
	return (res);
}

void	ft_path(t_exegg *ppx, char **envp)
{
	ppx->path = get_path(envp);
	if (!ppx->path)
		exit(1);
	ppx->cpath = ft_split(ppx->path, ':');
}

void	ft_freech(t_exegg *ppx)
{
	int	i;

	i = -1;
	while (ppx->cargs[++i])
		free(ppx->cargs[i]);
	i = -1;
	while (ppx->cpath[++i])
		free(ppx->cpath[i]);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	free(ppx->cpath);
	free(ppx->cargs);
	free(ppx->cmd);
}

void	ft_freedad(t_exegg *ppx, char **av)
{
	int	i;

	i = (!(ft_strncmp("here_doc", av[1], -1))) + 2;
	while (i < ppx->nb_arg)
	{
		wait(NULL);
		i++;
	}
	i = -1;
	while (ppx->cpath[++i])
		free(ppx->cpath[i]);
	free(ppx->cpath);
}

void	ft_error(int flg, t_exegg *ppx)
{
	int	i;

	if (flg == 1)
		ft_putendl_fd("Error with the input/output files", 2);
	if (flg == 0)
		ft_putendl_fd("Error with forking", 2);
	i = -1;
	if (!ppx)
		exit (1);
	while (ppx->cpath[++i])
		free(ppx->cpath[i]);
	free(ppx->cpath);
	exit(1);
}
