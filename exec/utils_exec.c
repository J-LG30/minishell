/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:54 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/23 19:07:37 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_path(t_env	*env)
{
	char	*res;
	t_env	*temp;

	res = NULL;
	temp = env;
	while (temp)
	{
		if ((temp && temp->vr) && (ft_strlen(temp->vr) >= 5 && ft_strncmp(temp->vr, "PATH=", 5) == 0))
		{
			res = temp->vr + 5;
			break ;
		};
		temp = temp->next;
	}
	if (res == NULL)
	{
		ft_putendl_fd("Path not found", 2);
		return (NULL);
	}
	return (res);
}

void	ft_path(t_exegg *exe, t_env *env)
{
	exe->path = get_path(env);
	if (!exe->path)
		exit(1);
	exe->cmdpath = ms_split(exe->path, ':');
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

static char	**freethem(char **ss)
{
	int	i;

	i = 0;
	while (ss[i] != 0)
	{
		free(ss[i]);
		i++;
	}
	free(ss);
	return (NULL);
}

static int	words(char const *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			wc++;
		i++;
	}
	return (wc);
}

static int	letters(char const *s, char c, int i)
{
	int	l;

	l = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			break ;
		i++;
		l++;
	}
	return (l + 1);
}

char	**ms_split(char const *s, char c)
{
	int		i;
	int		st;
	char	**res;

	res = malloc(sizeof(char *) * (words(s, c) + 1));
	if (!res)
		return (NULL);
	st = 0;
	i = 0;
	while (s[st] != '\0')
	{
		if (s[st] != c)
		{
			res[i] = ft_substr(s, st, letters(s, c, st));
			if (!res[i++])
				return (freethem(res));
			st += letters(s, c, st);
		}
		else
			st++;
	}
	res[i] = NULL;
	return (res);
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
		echo(cmds->full_cmd, flg);
	if (ft_strcmp(cmds->full_cmd[0], "pwd") == 0)
		pwd(flg);
	else if (ft_strcmp(cmds->full_cmd[0], "cd") == 0)
		cd(cmds->full_cmd[1], flg);
	else if (ft_strcmp(cmds->full_cmd[0], "export") == 0)
		export(cmds, exe->pkcenter, flg);
	else if (ft_strcmp(cmds->full_cmd[0], "env") == 0)
		env(exe->pkcenter, exe->pkcenter->envr, 0, flg);
	else if (ft_strcmp(cmds->full_cmd[0], "unset") == 0)
		return ;
	else if (ft_strcmp(cmds->full_cmd[0], "exit") == 0)
		return ;
}
