/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:18:31 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:15:33 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Similar to memcpy but use if memory areas overlap as safer approach
#include "libft.h" 

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (n == 0)
		return (dest);
	if (s < d)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
/*
#include <string.h>
int main(void)
{
	char str[50] = "hello";
	char str2[50] = "bloop";
	char s[] = {65, 66, 67, 68, 69, 0, 45};
	char s0[] = { 0,  0,  0,  0,  0,  0, 0};
	char sResult[] = {67, 68, 67, 68, 69, 0, 45};
	char sResult2[] = {67, 67, 68, 68, 69, 0, 45};
	
	char *a = ft_memmove(sResult + 1, sResult, 2);
	char *b = memmove(sResult + 1, sResult, 2);
	printf("Expected: %s\nGot: %s\n", b, a);
	return (0);
}
*/