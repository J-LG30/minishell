/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:18:58 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/01 17:31:51 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_dotslash(char *str)
{
	if (str[0] == '/' && str[ft_strlen(str) - 1] != '/')
		return (1);
	if (str[0] == '.' && str[1] == '/' && str[ft_strlen(str) - 1] != '/')
		return (1);
	if (str[ft_strlen(str) - 1] == '/')
		return (0);
	return (0);
}
