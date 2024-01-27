/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:02:28 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:15:49 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Copy n characters from src to dest
#include "libft.h" 

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
int main(void)
{
	char str[50] = "hello";
	char str2[50] = "bloop";

	char *a = ft_memcpy(((void*)0), ((void*)0), 3);
	printf("%s\n", a);
	return (0);
}
*/