/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:03:37 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:03:20 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Searches for first occurence and c and returns pointer s
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	c2;
	int				i;

	i = 0;
	c2 = (unsigned char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == c2)
		{
			s += i;
			return ((char *)(s));
		}
		i--;
	}
	return (0);
}
/*
#include <string.h>
int main(void)
{
	char *a = "hello";
	char s[] = "tripouille";
	char s3[] = "";
	
	printf("Expected: %s\nGot: %s\n", strrchr(s, 't' + 256), 
			ft_strrchr(s, 't' + 256));
}
*/
