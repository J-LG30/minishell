/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:19:12 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/18 18:23:24 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		j;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (0);
	start = 0;
	while (in_set(s1[start], set) == 1 && s1[start] != '\0')
			start++;
	end = ft_strlen(s1);
	while (in_set(s1[end - 1], set) && s1[end - 1] != '\0' && end > start)
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (0);
	j = 0;
	while (start != end)
	{
		str[j] = s1[start];
		j++;
		start++;
	}
	str[j] = '\0';
	return (str);
}

/*
#include <string.h>
int main(void)
{
	
	char *a = "//-/holydht--/-/-";
	char *set = "/-";
	char *b = "hello";
	char *c = "";
	char *d = "";
	char *place = " \n\t";
	printf("%s\n", ft_strtrim(a, set));
	printf("%s\n", ft_strtrim(b, set));
	printf("%s\n", ft_strtrim(c, d));
	printf("%p\n", ft_strtrim(0, 0));
	char *ret = ft_strtrim(c, place);
	
	char *str = ft_strtrim("   xxx   xxx", " x");
	if (!strcmp(str, ""))
	{
		printf("wooodjfo\n");
	}
}
*/
