/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:04:17 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/21 18:57:51 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	i = 0;
	if (s == NULL)
		return (0);
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	while (s[start + i] != 0 && i < len)
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (0);
	i = 0;
	while (len > 0 && s[start] != '\0')
	{
		str[i] = s[start];
		start++;
		i++;
		len--;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <string.h>
int main(void)
{
char *a = NULL;
char *b = "icecream";
char *c = "";
char    *test = "lorem ipsum dolor sit amet";
char *str = "01234";
size_t size = 10;

printf("%p\n", ft_substr(a, 4, 2));
printf("%s\n", ft_substr(str, 0, 18446744073709551615));
printf("%p\n", ft_substr(b, 20, 9));
printf("%s\n", ft_substr(c, 0, 0));
printf("%s\n", ft_substr(test, 0, 10));
}
*/
