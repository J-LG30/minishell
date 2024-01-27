/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:18:59 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/18 18:11:29 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c2;

	c2 = (unsigned char)c;
	while (1)
	{
		if (*s == c2)
			return ((char *)(s));
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (0);
}
/*
#include <string.h>
int main(void)
{
	char s[] = "tripouille";
	char *a = "hello";
	printf("Expected: %s\nGot: %s\n", strchr(s, 0), ft_strchr(s, 0));
}
*/