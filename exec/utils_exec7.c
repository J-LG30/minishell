/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:51:29 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/07 19:54:44 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	take_out(t_exegg *exe, t_ast *temp)
{
	int	fd;

	exe->out_value = temp->value;
	if (exe->btin && exe->fd_out < 0
		|| (ft_strcmp(exe->in_value, exe->out_value) == 0 && exe->err))
		fd_message(temp, exe);
	fd = open(exe->out_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		fd_message(temp, exe);
	if (exe->fd_out != STDOUT_FILENO)
		close(exe->fd_out);
	exe->fd_out = fd;
}
