/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:00:38 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/18 18:17:10 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

/*
#include <string.h>
int	main(void)
{
	char arr[] = "hello";
	char arr2[20];
	char src[] = "coucou";
	char dest[10]; memset(dest, 'A', 10);

	ft_strlcpy(dest, src, 1);
	printf("%s", dest);

	if (ft_strlcpy(dest, src, 1) == strlen(src))
		printf("yippee");
}
*/