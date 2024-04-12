/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:18:40 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/11 17:10:42 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Copies character c to first n characters of str s
#include "libft.h" 

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

/* int main(void)
{
	char str[50] = "What is up dudes.";
	printf("\nBefore memset(): %s\n", str);
  
	// Fill 8 characters starting from str[13] with '.'
	ft_memset(str + 13, '.', 8*sizeof(char));
  
	printf("After memset():  %s", str);
	return 0;
} */
