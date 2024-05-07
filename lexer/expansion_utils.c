/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:41:31 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/07 18:59:42 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*expand_status(t_shelgon *sh, char *line, char *tok_str, int index)
{
	int		i;
	int		j;
	char	*new;
	char	*trim_l;
	int		size;

	i = 0;
	trim_l = ft_itoa(sh->status);
	i++;
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
	free(trim_l);
	return (new);
}

int	while_var(char *str, int i)
{
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

int	only_var(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[++i])
			{
				if (str[i] == ' ' || str[i] == '\'' || str[i] == '"')
					return (0);
			}
			return (1);
		}
		if (!str[i])
			return (0);
		i++;
	}
	return (0);
}

void	check_mult_tok(t_token *token, t_shelgon *shelgon)
{
	char	**tokens;
	int		i;

	if (!token->value || !token->copy)
		return ;	
	i = only_var(token->copy);
	if (i == 0)
		return ;
	if (var_only_one(token->value))
		return (trimming_var(token));
	else
	{
		tokens = ms_split(token->value, ' ');
		if (!tokens)
			return ;
		i = 0;
		while (tokens[i])
			i++;
		if (i == 1)
			return (token_help(tokens));
		free(token->value);
		token->value = ft_strdup(tokens[0]);
		if (token_loop(tokens, shelgon, token))
			return ;
	}
	return ;
}
