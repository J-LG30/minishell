/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:43:25 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 17:04:56 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Tries to find first occurence of s2 in s1 in n first characters
#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)(s1));
	while (s1[i] != '\0' && n > 0)
	{
		if (s1[i] == s2[0] && n >= ft_strlen(s2))
		{
			k = i;
			j = 0;
			while (s2[j] != '\0' && s1[k] == s2[j])
			{
				j++;
				k++;
			}
			if (s2[j] == '\0')
				return ((char *)(&s1[i]));
		}
		i++;
		n--;
	}
	return (0);
}
/*
int     main(void)
{
   char *a = "holiday";
   char *e = "hooolidayboolidaygolyholidayfolly";
   char haystack[30] = "aaabcabcd";

   if (ft_strnstr(haystack, "cd", 8) == NULL)
	printf("wabdaweeeeeee\n");
}
*/