/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:57:51 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/03 13:00:42 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_heredoc(char *line, int i, int j, t_shelgon *shelgon)
{
	char	*new_val;
	t_env	*env;

	if (i == -1)
	{
		i = while_var(line, j + 1);
		new_val = ft_rm_substr(line, j, i - 1);
		free(line);
		line = new_val;
		j--;
	}
	else if (i >= 0)
	{
		env = return_index(shelgon->env, i);
		if (i > 0)
			new_val = expanded(shelgon, env->vr, line, j + 1);
		else
			new_val = expand_status(shelgon, env->vr, line, j + 1);
		if (!new_val)
			return (0);
		free(line);
		line = new_val;
	}
	return (line);
}

char	*check_heredoc(char *line, t_shelgon *shelgon)
{
	int		i;
	int		j;
	t_env	*env;
	char	*new_val;

	env = shelgon->env;
	j = 0;
	new_val = line;
	while (line && line[j])
	{
		if (line[j] == '$')
		{
			i = var_status(&line[j + 1], env);
			new_val = expand_heredoc(line, i, j, shelgon);
			line = new_val;
		}
		if (!line || !line[j])
			break ;
		j++;
	}
	if (!new_val)
		return (ft_strdup(""));
	return (new_val);
}

int	check_dotslash(char *str)
{
	if (!str)
		return (0);
	if (str[0] && str[0] == '/' && str[ft_strlen(str) - 1] != '/')
		return (1);
	if (str[0] && str[0] == '.' && str[1] == '/'
		&& str[ft_strlen(str) - 1] != '/')
		return (1);
	if (str[0] && str[ft_strlen(str) - 1] == '/')
		return (0);
	return (0);
}

int	redir_del(t_ast *temp, t_branch *cur, t_branch *last, t_branch **cmds)
{
	int	i;

	i = 1;
	if (temp && temp->type == WORD)
		i = 1;
	else if (temp && temp->type == REDIR_DELIMIT)
		i = pr_her(temp, cur, last, cmds);
	return (i);
}

int	here_help(int std_in, char *res, int *fd)
{
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	rl_replace_line("", 0);
	free(res);
	close(fd[1]);
	close(std_in);
	return (fd[0]);
}
