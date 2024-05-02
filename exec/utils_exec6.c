/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:22:45 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/02 21:29:14 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_loop(char *res, int *fd, t_ast *temp, t_shelgon *shelgon)
{
	int	std_in;

	std_in = dup(STDIN_FILENO);
	while (1)
	{
		res = readline("> ");
		if (g_sig == 1)
			return(here_help(std_in, res, fd));
		if (!res)
			return (err_heredoc(fd, std_in, res));
		if (temp->heredoc)
			res = check_heredoc(res, shelgon);
		if (ft_strncmp(temp->value, res, ft_strlen(temp->value)) == 0
			&& (ft_strlen(temp->value) == ft_strlen(res)))
			break ;
		ft_putendl_fd(res, fd[1]);
		free(res);
	}
	return (-4);
}
