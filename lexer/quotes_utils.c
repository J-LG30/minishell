/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:25:37 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/07 19:30:09 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	translation_str(t_token *token)
{
	int		i;
	char	*new_val;
	int		exp;

	i = 0;
	exp = 1;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
			exp *= -1;
		if (token->value[i] == '$' && token->value[i + 1] == '"' && exp == 1)
		{
			new_val = ft_rm_substr(token->value, i, i + 1);
			if (!new_val)
				return ;
			free(token->value);
			token->value = new_val;
			i = -1;
		}
		i++;
	}
}

int	what_return(int closed, char q)
{
	if (closed == -1 && q != '\0')
		return (1);
	return (0);
}

int	help_unc_quotes(int closed, t_token *token)
{
	token->has_quotes = 1;
	closed *= -1;
	return (closed);
}

char	*rm_quotes_loop(char *new_val, int size, t_token *token)
{
	int		j;
	int		i;
	char	q;

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
