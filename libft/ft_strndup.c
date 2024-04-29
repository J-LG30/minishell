/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:31:36 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/28 16:13:30 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ft_strdup but copies the first n characters + null terminator
//if n is bigger than src str length then functionally acts as ft_strdup 
char	*ft_strndup(char *src, size_t n)
{
	char	*dst;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (n <= 0)
		return (NULL);
	if (n >= src_len)
		dst = malloc(ft_strlen(src) + 1);
	else
		dst = malloc(n + 1);
	if (dst == NULL)
		return (NULL);
	else
		ft_memcpy(dst, src, n + 1);
	return (dst);
}
