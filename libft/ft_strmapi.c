/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:21:00 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:12:42 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Passes each char of s into f function creating a new string str
//which we return
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (s == NULL || f == NULL)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = (f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char    test(unsigned int i, char c)
{
	return (i + c);
}
#include <string.h>
int main(void)
{
	char *a = "hello";
	char *b = "	~~~~~";
	char * s = ft_strmapi("1234", test);
	if (!strcmp(s, "1357"))
		printf("yipee");
	printf("%s\n", s);
	printf("%s\n", ft_strmapi(a, test));
	printf("%s\n", ft_strmapi(b, test));
	printf("%p\n", ft_strmapi(0, test));
	printf("%p\n", ft_strmapi(a, 0));
}
*/