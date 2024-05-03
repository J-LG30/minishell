/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:25:37 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/03 11:16:31 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	translation_str(t_token *token)
{
	int		i;
	char	*new_val;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->value[i + 1] == '"')
		{
			new_val = ft_rm_substr(token->value, i, i);
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

// char	*rm_quotes_helper(t_token *token)
// {
// }
