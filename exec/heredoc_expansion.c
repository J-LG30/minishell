/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:57:51 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/30 14:53:51 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_heredoc(char *line, int i, int j, t_shelgon *shelgon)
{
	char	*new_val;
	t_env	*env;

	if (i == -1)
	{
		i = j + 1;
		while (ft_isalnum(line[i]) || line[i] == '_')
			i++;
		new_val = ft_rm_substr(line, j, i - 1);
		free(line);
		line = new_val;
		j--;
	}
	else if (i >= 0)
	{
		env = return_index(shelgon->env, i);
		new_val = expanded(shelgon, env->vr, line, j + 1, i);
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
	
	while (line[j])
	{
		if (line[j] == '$')
		{
			i = var_status(&line[j + 1], env);
			new_val = expand_heredoc(line, i, j, shelgon);
		}
		j++;
	}
	return (new_val);
}
