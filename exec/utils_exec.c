/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:54 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/09 18:56:27 by jle-goff         ###   ########.fr       */
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
		if (ft_strlen(envp[i]) >= 5 && ft_strncmp(envp[i], "PATH=", 5) == 0)
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

void	ft_path(t_exegg *exe)
{
	exe->path = get_path(exe->pkcenter->envr);
	if (!exe->path)
		exit(1);
	exe->cmdpath = ft_split(exe->path, ':');
}

/* void	ft_freech(t_exegg *exe)
{
	int	i;

	i = -1;
	while (cmds->args[++i])
		free(exe->cargs[i]);
	i = -1;
	while (exe->cpath[++i])
		free(exe->cpath[i]);
	close(exe->fd[0]);
	close(exe->fd[1]);
	free(exe->cpath);
	free(exe->cargs);
	free(exe->cmd);
} */

/* void	ft_freedad(t_exegg *exe, char **av)
{
	int	i;

	i = (!(ft_strncmp("here_doc", av[1], -1))) + 2;
	while (i < exe->nb_arg)
	{
		wait(NULL);
		i++;
	}
	i = -1;
	while (exe->cpath[++i])
		free(exe->cpath[i]);
	free(exe->cpath);
} */

void	ft_error(int flg, t_exegg *exe)
{
	int	i;

	if (flg == 1)
		ft_putendl_fd("Error with the input/output files", 2);
	if (flg == 0)
		ft_putendl_fd("Error with forking", 2);
	i = -1;
	if (!exe)
		exit (1);
	while (exe->cmdpath[++i])
		free(exe->cmdpath[i]);
	free(exe->cmdpath);
	exit(1);
}

t_branch	*msh_lstlast(t_branch *lst)
{
	t_branch	*next;

	printf("a\n");
	if (lst == NULL)
		return (0);
	printf("b\n");
	next = lst -> next;
	printf("c\n");
	while (next != NULL)
	{
		printf("d\n");
		lst = next;
		next = lst -> next;
		printf("e\n");
	}
	printf("f\n");
	
	return (lst);
}
