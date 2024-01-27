/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:52:56 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/18 18:07:45 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s != 0 || fd >= 0)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}
/*
#include <fcntl.h>
int main(void)
{
	int fd;
	char * a = "acoording to alll known laws of aviation";

	fd = open("Output.txt", O_WRONLY);
	ft_putstr_fd(a, fd);
}
*/