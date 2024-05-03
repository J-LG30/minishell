/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:41:31 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/03 12:12:28 by jle-goff         ###   ########.fr       */
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
			while (str[i])
			{
				if (str[i] == ' ')
					return (0);
				i++;
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
	t_token	*new;
	t_token	*subhead;

	subhead = NULL;
	i = only_var(token->copy);
	if (i == 0)
		return ;
	if (i == 1)
	{
		tokens = ms_split(token->value, ' ');
		if (!tokens)
			return ;
		i = 0;
		while (tokens[i])
			i++;
		if (i == 1)
		{
			free(tokens[0]);
			free(tokens);
			return ;
		}
		free(token->value);
		token->value = ft_strdup(tokens[0]);
		i = 1;
		while (tokens[i])
		{
			new = ft_new_token(shelgon);
			if (!new)
				return ;
			new->type = WORD;
			new->value = ft_strdup(tokens[i]);
			new->copy = ft_strdup(new->value);
			ft_tokenadd_back(&subhead, new);
			handle_word(new, shelgon, token);
			i++;
		}
		i = -1;
		while (tokens[++i])
			free(tokens[i]);
		free(tokens);
		token->next->prev = new;
		new->next = token->next;
		subhead->prev = token;
		token->next = subhead;
	}
	return ;
}
