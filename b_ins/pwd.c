/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:35:42 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/25 17:24:57 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(int flg, t_shelgon *shelgon)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putendl_fd("ERROR MESSAGE", 2);
	else
		printf("%s\n", cwd);
	shelgon->status = 0;
	if (flg)
		return ;
	exit (1);
}
