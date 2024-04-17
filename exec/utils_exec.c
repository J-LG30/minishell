/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:54 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/16 15:48:11 by davda-si         ###   ########.fr       */
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
	if (ft_strncmp(cmds, "echo", ft_strlen(cmds)) == 0)
		return (1);
	else if (ft_strncmp(cmds, "pwd", ft_strlen(cmds)) == 0)
		return (1);
	else if (ft_strncmp(cmds, "cd", ft_strlen(cmds)) == 0)
		return (1);
	else if (ft_strncmp(cmds, "export", ft_strlen(cmds)) == 0)
		return (1);
	else if (ft_strncmp(cmds, "env", ft_strlen(cmds)) == 0)
		return (1);
	else if (ft_strncmp(cmds, "unset", ft_strlen(cmds)) == 0)
		return (1);
	else if (ft_strncmp(cmds, "exit", ft_strlen(cmds)) == 0)
		return (1);
	else
		return (0);
}
