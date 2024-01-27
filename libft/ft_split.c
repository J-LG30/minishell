/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:17:17 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/21 19:35:59 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cp_word(char const *s, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (0);
	while (start < end)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

int	str_size(char const *s, int index, char c)
{
	int	size;

	size = 0;
	while (s[index] != c && s[index] != '\0')
	{
		index++;
		size++;
	}
	return (size);
}

int	count_words(char const *s, char c)
{
	int	numstr;
	int	i;

	i = 0;
	numstr = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			numstr++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (numstr);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		num;
	int		end;
	int		words;

	i = 0;
	num = 0;
	str = malloc(sizeof(char *) * (count_words(s, c) + 1));
	words = count_words(s, c);
	if (str == NULL)
		return (0);
	while (s[i] && num < words)
	{
		while (s[i] == c)
			i++;
		end = str_size(s, i, c);
		str[num] = cp_word(s, i, end + i);
		if (str[num] == NULL)
			return (0);
		i += end;
		num++;
	}
	str[num] = 0;
	return (str);
}

/*
int main(void)
{
	char *a = "chinimala";
	char c = ' ';
	printf("%s\n", ft_split(a, c)[4]);
}
*/
