/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:45:36 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/19 16:54:16 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unclosed_quotes(t_token *token)
{
	int		flag;
	int		i;
	int		closed;
	char	q;

	i = 0;
	closed = -1;
	while (token->value[i])
	{
		while (token->value && token->value[i] != '\'' && token->value[i] != '"')
			i++;
		if (!token->value[i])
			break ;
		if (token->value[i] == '"')
			q = token->value[i];
		else if (token->value[i] == '\'')
			q = token->value[i];
		while (token->value[++i])
		{
			if (token->type == D_STR && token->value[i] == '"')
				closed *= -1;
			else if (token->type == S_STR && token->value[i] == '\'')
				closed *= -1;
		}
	}
	if (closed == -1 && (token->type == D_STR || token->type == S_STR))
		return (1);
	return (0);
}

int	which_quote(t_token *token)
{
	int quote;
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			quote = 1;
			return (1);
		}
		if (token->value[i] == '"')
		{
			quote = 2;
			return (2);
		}
		i++;
	}
	return (0);
}

//flag == 1 means inside a quoted str, dont remove any quotes
int	size_wo_quotes(t_token *token)
{
	char	*new_val;
	char	q;
	int		i;
	int		size;
	int		j;

	i = 0;
	size = 0;
	q = '\0';
	while (token->value[i])
	{
		if ((token->value[i] == '\'' || token->value[i] == '"') && q == '\0')
			q = token->value[i];
		else if (token->value[i] == q)
			q = '\0';
		else if (token->value[i] != q)
			size++;
		i++;
	}
	return (size);
}

void	rm_quotes(t_token *token)
{
	int		size;
	char	*new_val;
	int		i;
	int		j;
	char	q;

	size = size_wo_quotes(token);
	new_val = malloc(sizeof(char) * (size + 1));
	if (!new_val)
		return ;
	i = 0;
	j = 0;
	q = '\0';
	while (j < size)
	{
		if ((token->value[i] == '\'' || token->value[i] == '"') && q == '\0')
			q = token->value[i];
		else if (token->value[i] == q)
			q = '\0';
		else if (token->value[i] != q)
		{	
			new_val[j] = token->value[i];
			j++;	
		}
		i++;
	}
	new_val[j] = '\0';
	free(token->value);
	token->value = new_val;
	
}

//MALLOC error at return
// void	rm_quotes(t_token *token)
// {
// 	char	*new_val;
// 	int		size;
// 	int		i;
// 	int		j;

// 	if (token->type == D_STR)
// 		new_val = ft_strtrim(token->value, "\"");
// 	else if (token->type == S_STR)
// 		new_val = ft_strtrim(token->value, "'");
// 	if (!new_val)
// 		return ;
// 	free(token->value);
// 	token->value = new_val;
	//printf("in rm quote\n");
	// size = 0;
	// i = 0;
	// //printf("1\n");
	// while (token->value[i])
	// {
	// 	if (token->value[i] != '\'' && token->value[i] != '"')
	// 		size++;
	// 	i++;
	// }
	// new_val = malloc(sizeof(char) * (size + 1));
	// if (!new_val)
	// 	return ;
	// j = 0;
	// i = 0;
	// while (size > 0)
	// {
	// 	if (token->value[i] != '\'' && token->value[i] != '"')
	// 	{
	// 		new_val[j] = token->value[i];
	// 		//printf("%c", new_val[j]);
	// 		j++;
	// 		size--;
	// 	}
	// 	i++;
	// }
	// new_val[j] = '\0';
	// free(token->value);
	// //printf("%s\n", new_val);
	// token->value = new_val;
//}

//might remove a token if it cant expand instead we shall see
void	expansion(t_token *token, t_shelgon *shelgon)
{
	int		i;
	int		j;
	char	**env;
	char	*new_val;
	char	*temp;

	env = shelgon->envr;
	j = 0;
	while (token->value[j])
	{
		if (token->value[j] == '$')
		{
			i = 0;
			while (env[i])
			{
				temp = &token->value[j + 1];
				if (!ft_strncmp(temp, env[i], ft_strlen(temp))
					&& env[i][ft_strlen(temp)] == '=')
				{
					new_val = malloc(sizeof(char)
							* (ft_strlen(env[i]) - ft_strlen(temp)));
					j = ft_strlen(temp);
					temp = &env[i][j + 1];
					ft_strlcpy(new_val, temp, ft_strlen(temp) + 1);
					free(token->value);
					token->value = new_val;
					return ;
				}
				i++;
			}
			free(token->value);
			token->value = malloc(sizeof(char) * 1);
			token->value[0] = '\0';
		}
		j++;
	}
}

//print error message
int	handle_word(t_token *token, t_shelgon *shelgon)
{
	// if (unclosed_quotes(token))
	// {
	// 	ft_putstr_fd("Error: Unclosed quotes\n", 2);
	// 	return (1);
	// }
	rm_quotes(token);
	if (token->type != S_STR && !ft_strcmp(token->value, "$?"))
	{
		free(token->value);
		token->value = ft_itoa(shelgon->status);
	}
	else if (token->type != S_STR)
	{
		expansion(token, shelgon);
	}
	token->type = WORD;
	return (0);
}
