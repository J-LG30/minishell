/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:02 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/25 17:43:15 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cd(char *arg, int flg, t_shelgon *shelgon)
{
	if (chdir(arg) != 0)
	{
		ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: cd: ", 2);
		if (arg)
			ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		shelgon->status = 1;
	}
	if (flg)
		return ;
	exit (0);
}
