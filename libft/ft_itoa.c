/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:05:38 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/18 17:57:28 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	size_str(long n)
{
	int	sign;
	int	digits;

	sign = 0;
	digits = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits + sign + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		i;
	long	num;

	num = (long)(n);
	size = size_str((long)n);
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (0);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	str[size - 1] = '\0';
	if (num == 0)
		str[0] = '0';
	i = size - 2;
	while (num > 0)
	{
		str[i--] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}
/*
int main(void)
{
	int a = 0;
	int b = 4567;
	int c = -346;
	int d = -1;
	int e = 2147483647;
	int f = -2147483648;
	printf("%s\n", ft_itoa(a));
	printf("%s\n", ft_itoa(b));
	printf("%s\n", ft_itoa(c));
	printf("%s\n", ft_itoa(d));
	printf("%s\n", ft_itoa(e));
	printf("%s\n", ft_itoa(f));
}
*/
