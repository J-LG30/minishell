/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:59:35 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/19 16:44:43 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c2;
	size_t			i;

	c2 = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*str == c2)
			return (str);
		i++;
		str++;
	}
	return (0);
}

/*
#include <string.h>
int main(void)
{
	char str[50] = "hello";
	char str2[50] = "mello";
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	char *a = ft_memchr(s, 2 + 256, 3);
	char *b = memchr(s, 2 + 256, 3);
	printf("Expected: %c\nGot: %c\n", *b, *a); 
	printf("%c\n", *b);   
	return (0);
}
*/
