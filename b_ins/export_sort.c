/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:41:47 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/02 16:53:11 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_sort(char **copy)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	while (1)
	{
		flag = 0;
		i = 0;
		while (copy && copy[i])
		{
			if (copy && copy[i] && copy[i + 1]
				&& ft_strcmp(copy[i], copy[i + 1]) >= 0)
			{
				flag = 1;
				tmp = copy[i];
				copy[i] = copy[i + 1];
				copy[i + 1] = tmp;
			}
			i++;
		}
		if (flag == 0)
			break ;
	}
}

char	**sort_exp(t_shelgon *shell, char **copy)
{
	t_env	*tmp;
	char	*var_tmp;
	int		i;

	tmp = shell->env;
	i = 0;
	copy = (char **)malloc(sizeof(char *) * (ms_lstsize(tmp) + 1));
	if (!copy)
		return (NULL);
	while (tmp)
	{
		copy[i] = tmp->cpy;
		tmp = tmp->next;
		i++;
	}
	copy[i] = NULL;
	print_sort(copy);
	return (copy);
}

static int	size_quotes(char *str)
{
	char	q;
	int		i;
	int		size;
	int		j;

	i = 0;
	size = 0;
	q = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && q == '\0')
			q = str[i];
		else if (str[i] == q)
			q = '\0';
		else if (str[i] != q)
			size++;
		i++;
	}
	return (size);
}

char	*rm_quo(char *str)
{
	int		size;
	char	*new_val;
	int		i;
	int		j;
	char	q;

	size = size_quotes(str);
	new_val = malloc(sizeof(char) * (size + 1));
	if (!new_val)
		return (NULL);
	i = 0;
	j = 0;
	q = '\0';
	while (j < size)
	{
		if ((str[i] == '\'' || str[i] == '"') && q == '\0')
			q = str[i];
		else if (str[i] == q)
			q = '\0';
		else if (str[i] != q)
			new_val[j++] = str[i];
		i++;
	}
	new_val[j] = '\0';
	return (new_val);
}
