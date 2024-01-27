/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:13:05 by jle-goff          #+#    #+#             */
/*   Updated: 2023/04/24 19:54:29 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Initializes all allocated memory to 0
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
/*
int main(void)
{
	void *a = ft_calloc(0, 0);
	printf("Output -> %p", a);
	if (a == ((void*)0))
 		printf("test failed");

}
*/
