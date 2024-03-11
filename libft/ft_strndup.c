#include "libft.h"

//ft_strdup but only copies n chars of the string. if n is bigger than string it copies the whole string but
//does not add any extra chars at the end.
char	*ft_strndup(char *src, int n)
{
	char	*dst;
	int		copy_len;

	if (n <= 0)
		return (NULL);
	copy_len = ft_strlen(src);
	if (n < copy_len)
		copy_len = n;
	dst = malloc(copy_len + 1);
	if (dst == NULL)
		return (NULL);
	else
		ft_memcpy(dst, src, copy_len + 1);
	return (dst);
}