/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:58:08 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 20:00:21 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Copies from src to dest until n bytes are copied or char c is found
#include "libft.h" 

void	*ft_memccpy(void *dest, void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		if (d[i] == c)
			return (dest + i + 1);
		d[i] = s[i];
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	char str[50] = "hello";
	char str2[50] = "mello";
	char *a = ft_memccpy(str, str2, 101, 3);
	printf("%s\n", a);    
	return (0);
}
*/