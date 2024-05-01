/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:18:58 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/01 17:53:29 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_dotslash(char *str)
{
	if (str && str[0])
	{
		if (str[0] == '/' && str[ft_strlen(str) - 1] != '/')
			return (1);
		if (str[0] == '.' && str[1] == '/' && str[ft_strlen(str) - 1] != '/')
			return (1);
		if (str[ft_strlen(str) - 1] == '/')
			return (0);	
	}
	return (0);
}
