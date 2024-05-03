/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:12:20 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/03 11:14:24 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// j is the index to env str with var, or -1 if n/a, or 0 if its $? special case
int	var_status(char *str, t_env *env)
{
	int		i;
	int		j;
	int		exit;
	t_env	*t;

	i = 0;
	if (str[0] == '_')
		return (-2);
	if (str[0] == '?')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == 0)
		return (-2);
	j = 0;
	t = env;
	while (t)
	{
		if (!ft_strncmp(str, t->vr, i) && t->vr[i] == '=' && t->vr[i + 1])
			return (j);
		j++;
		t = t->next;
	}
	return (-1);
}

char	*expanded(t_shelgon *shelgon, char *line, char *tok_str, int index)
{
	int		i;
	int		j;
	char	*new;
	char	*trim_l;
	int		size;

	i = 0;
	trim_l = ft_strchr(line, '=');
	if (!trim_l)
		return (NULL);
	trim_l++;
	while (line[i] && line[i] != '=')
		i++;
	size = ft_strlen(tok_str) + ft_strlen(trim_l) - i + 1;
	new = malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	ft_memset(new, 'a', size);
	new[size - 1] = '\0';
	ft_strlcpy(new, tok_str, index);
	ft_strlcat(new, trim_l, size);
	while (index + i-- > 0)
		tok_str++;
	ft_strlcat(new, tok_str, size);
	return (new);
}

//norming might have changed this
char	*ft_rm_substr(char *str, int start, int end)
{
	char	*new;
	int		i;
	int		j;

	if (end - start <= 0)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) - (end - start) + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (i < start || i > end)
			new[j++] = str[i];
	}
	if (j == 0)
	{
		free(new);
		return (NULL);
	}
	new[j] = '\0';
	return (new);
}

int	expand_util_cases(t_token *token, int i, int j, t_shelgon *shelgon)
{
	char	*new_val;
	t_env	*env;

	if (i == -1)
	{
		i = while_var(token->value, j + 1);
		new_val = ft_rm_substr(token->value, j, i - 1);
		free(token->value);
		token->value = new_val;
		j--;
	}
	else if (i >= 0)
	{
		env = return_index(shelgon->env, i);
		if (i > 0)
			new_val = expanded(shelgon, env->vr, token->value, j + 1);
		else
			new_val = expand_status(shelgon, env->vr, token->value, j + 1);
		if (!new_val)
			return (0);
		free(token->value);
		token->value = new_val;
	}
	return (j);
}

void	expansion(t_token *token, t_shelgon *shelgon)
{
	int		i;
	int		j;
	t_env	*env;
	char	*new_val;
	int		expand[2];

	env = shelgon->env;
	j = 0;
	expand[0] = 1;
	expand[1] = 1;
	while (token->value && token->value[j])
	{
		if (token->value[j] == '"')
			expand[1] *= -1; 
		if (token->value[j] == '\'' && expand[1] > 0)
			expand[0] *= -1;
		else if (token->value[j] == '$' && expand[0] > 0)
		{
			i = var_status(&token->value[j + 1], env);
			j = expand_util_cases(token, i, j, shelgon);
		}
		j++;
	}
	return ;
}
