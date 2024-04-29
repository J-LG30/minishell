/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:49:57 by david             #+#    #+#             */
/*   Updated: 2024/04/28 20:53:48 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_path(t_exegg *exe, t_env *env)
{
	exe->path = get_path(env);
	if (!exe->path)
	{
		exe->cmdpath = NULL;
		return ;
	}
	exe->cmdpath = ms_split(exe->path, ':');
}

int	is_btin(char *cmds)
{
	if (ft_strcmp(cmds, "echo") == 0)
		return (1);
	if (ft_strcmp(cmds, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmds, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmds, "export") == 0)
		return (1);
	else if (ft_strcmp(cmds, "env") == 0)
		return (1);
	else if (ft_strcmp(cmds, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmds, "exit") == 0)
		return (1);
	else
		return (0);
}

void	run_btin(t_ast *tree, t_exegg *exe, t_branch *cmds, int flg)
{
	if (ft_strcmp(cmds->full_cmd[0], "echo") == 0)
		echo(cmds->full_cmd, flg, exe->pkcenter);
	if (ft_strcmp(cmds->full_cmd[0], "pwd") == 0)
		pwd(flg, exe->pkcenter);
	else if (ft_strcmp(cmds->full_cmd[0], "cd") == 0)
		cd(cmds->full_cmd[1], flg, exe->pkcenter);
	else if (ft_strcmp(cmds->full_cmd[0], "export") == 0)
		export(cmds, exe->pkcenter, flg);
	else if (ft_strcmp(cmds->full_cmd[0], "env") == 0)
		env(exe->pkcenter, exe->pkcenter->envr, 0, flg);
	else if (ft_strcmp(cmds->full_cmd[0], "unset") == 0)
		unset(exe->pkcenter, cmds->full_cmd, flg);
	else if (ft_strcmp(cmds->full_cmd[0], "exit") == 0)
		ft_exit(exe->pkcenter, cmds, exe);
	return ;
}

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
	t_branch	*ls;

	ls = lst;
	if (ls != NULL)
	{
		while (ls && ls->next)
			ls = ls->next;
	}
	else
		return (NULL);
	return (ls);
}
