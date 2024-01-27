/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:21:44 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/18 18:19:59 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp( const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (0);
	while (str1[i] == str2[i] && (str1[i] != '\0'
			|| str2[i] != '\0') && i < num - 1)
	{
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
/*
int	main(void)
{
	char *a = "he";
	char *b = "hello";

	printf("%i", ft_strncmp("test\200", "test\0", 6));
}
*/