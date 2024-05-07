/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:41:14 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/07 15:02:02 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_err_msg(char **full_cmd, t_shelgon *shelgon)
{
	ft_putendl_fd("exit (¬_¬)ﾉ", 1);
	ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: exit: ", 2);
	ft_putstr_fd(full_cmd[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	shelgon->status = 2;
}

void	finish_ex(t_exegg *exe, t_shelgon *shelgon, int status)
{
	exe->fd_in = dup2(exe->saved_file[0], STDIN_FILENO);
	exe->fd_out = dup2(exe->saved_file[1], STDOUT_FILENO);
	close(exe->saved_file[1]);
	close(exe->saved_file[0]);
	free_all(shelgon, shelgon->exe, BTIN);
	exit(status);
}

void	exit_err(t_shelgon *shelgon)
{
	free_all(shelgon, shelgon->exe, BTIN);
	exit (2);
}
