/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:45:36 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/28 15:44:47 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unclosed_quotes(t_token *token)
{
	int		i;
	int		closed;
	char	q;

	i = 0;
	closed = 1;
	while (token->value[i])
	{
		q = '\0';
		if (token->value[i] == '\'' || token->value[i] == '"')
		{
			closed *= -1;
			q = token->value[i];
			while (token->value[++i] && closed == -1)
			{
				if (token->value[i] == q)
					closed *= -1;
			}
		}
		i++;
	}
	if (closed == -1 && q != '\0')
		return (1);
	return (0);
}

int	which_quote(t_token *token)
{
	int	quote;
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			quote = 1;
			return (1);
		}
		if (token->value[i] == '"')
		{
			quote = 2;
			return (2);
		}
		i++;
	}
	return (0);
}

// flag == 1 means inside a quoted str, dont remove any quotes
int	size_wo_quotes(t_token *token)
{
	char	*new_val;
	char	q;
	int		i;
	int		size;
	int		j;

	i = 0;
	size = 0;
	q = '\0';
	while (token->value[i])
	{
		if ((token->value[i] == '\'' || token->value[i] == '"') && q == '\0')
			q = token->value[i];
		else if (token->value[i] == q)
			q = '\0';
		else if (token->value[i] != q)
			size++;
		i++;
	}
	return (size);
}

char	*rm_quotes(t_token *token)
{
	int		size;
	char	*new_val;
	int		i;
	int		j;
	char	q;

	size = size_wo_quotes(token);
	new_val = malloc(sizeof(char) * (size + 1));
	if (!new_val)
		return (NULL);
	i = 0;
	j = 0;
	q = '\0';
	while (j < size)
	{
		if ((token->value[i] == '\'' || token->value[i] == '"') && q == '\0')
			q = token->value[i];
		else if (token->value[i] == q)
			q = '\0';
		else if (token->value[i] != q)
			new_val[j++] = token->value[i];
		i++;
	}
	new_val[j] = '\0';
	return (new_val);
}

// print error message
int	handle_word(t_token *token, t_shelgon *shelgon)
{
	char	*new_val;

	if (unclosed_quotes(token))
	{
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
		return (1);
	}
	expansion(token, shelgon);
	new_val = rm_quotes(token);
	if (!new_val)
		return (1);
	free(token->value);
	token->value = new_val;
	token->type = WORD;
	return (0);
}
