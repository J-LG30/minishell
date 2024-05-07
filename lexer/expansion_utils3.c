/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:56:50 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/07 16:59:03 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	trimming_var(t_token *token)
{
	char	*new_val;

	new_val = NULL;
	if (!token->value)
		return ;
	else
	{
		new_val = ft_strtrim(token->value, " ");
		free(token->value);
		token->value = new_val;
	}
	return ;
}