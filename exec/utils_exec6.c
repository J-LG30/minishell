/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:22:45 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/03 12:20:17 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_loop(char *res, int *fd, t_ast *temp, t_shelgon *shelgon)
{
	int	std_in;

	printf("VALUE: %s TYPE: %d\n", temp->value, temp->type);
	std_in = dup(STDIN_FILENO);
	while (1)
	{
		res = readline("> ");
		if (g_sig == 1)
			return(here_help(std_in, res, fd));
		if (!res)
			return (err_heredoc(fd, std_in, res));
		if (ft_strncmp(temp->value, res, ft_strlen(temp->value)) == 0
			&& (ft_strlen(temp->value) == ft_strlen(res)))
			break ;
		if (temp->heredoc)
			res = check_heredoc(res, shelgon);
		ft_putendl_fd(res, fd[1]);
		free(res);
	}
	return (-4);
}
