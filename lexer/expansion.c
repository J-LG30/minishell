/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:12:20 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/30 13:25:20 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// j is the index to env str with var, or -1 if n/a, or 0 if its $? special case
int	var_status(char *str, t_env *env)
{
	int		i;
	int		j;
	int		exit;
	t_env	*temp;

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
	temp = env;
	while (temp)
	{
		if (!ft_strncmp(str, temp->vr, i) && temp->vr[i] == '=')
			return (j);
		j++;
		temp = temp->next;
	}
	return (-1);
}

char	*expanded(t_shelgon *shelgon, char *line, char *tok_str, int index,
		int flag)
{
	int		i;
	int		j;
	char	*new;
	char	*trim_l;
	int		size;

	printf("in expanded\n");
	i = 0;
	if (flag)
	{
		trim_l = ft_strchr(line, '=');
		if (!trim_l)
			return (NULL);
		trim_l++;
		while (line[i] && line[i] != '=')
			i++;
	}
	else
	{
		trim_l = ft_itoa(shelgon->status);
		i++;
	}
	if (!trim_l)
		return (NULL);
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
	if (!flag)
		free(trim_l);
	return (new);
}

char	*ft_rm_substr(char *str, int start, int end)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (ft_strlen(str) - (end - start) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i < start || i > end)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

t_env	*return_index(t_env *head, int index)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		if (i == index)
			return (temp);
		i++;
		temp = temp->next;
	}
	return (NULL);
}

int	expand_util_cases(t_token *token, int i, int j, t_shelgon *shelgon)
{
	char	*new_val;
	t_env	*env;

	if (i == -1)
	{
		i = j + 1;
		while (ft_isalnum(token->value[i]) || token->value[i] == '_')
			i++;
		new_val = ft_rm_substr(token->value, j, i - 1);
		free(token->value);
		token->value = new_val;
		j--;
	}
	else if (i >= 0)
	{
		env = return_index(shelgon->env, i);
		new_val = expanded(shelgon, env->vr, token->value, j + 1, i);
		if (!new_val)
			return (0);
		free(token->value);
		token->value = new_val;
	}
	return (j);
}

// might remove a token if it cant expand instead we shall see
void	expansion(t_token *token, t_shelgon *shelgon)
{
	int		i;
	int		j;
	t_env	*env;
	char	*new_val;
	int		expand;

	env = shelgon->env;
	j = 0;
	expand = 1;
	while (token->value[j])
	{
		if (token->value[j] == '\'')
			expand *= -1;
		else if (token->value[j] == '$' && expand > 0)
		{
			i = var_status(&token->value[j + 1], env);
			j = expand_util_cases(token, i, j, shelgon);
		}
		j++;
	}
}
