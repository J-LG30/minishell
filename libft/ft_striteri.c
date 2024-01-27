/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:52:23 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:13:14 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Passes each character of s through function f
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i])
	{
		ptr = &s[i];
		(f)(i, ptr);
		i++;
	}
}

/*
void    test(unsigned int i, char *c)
{
	*c += i;
}
int main(void)
{
	char a[50] = "hello";
	char b[50] = "	~~~~~";
	ft_striteri(a, test);
	printf("%s\n", a);
}
*/