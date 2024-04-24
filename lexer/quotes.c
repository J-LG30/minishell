/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:45:36 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/24 14:37:58 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unclosed_quotes(t_token *token)
{
	int		flag;
	int		i;
	int		closed;
	char	q;

	//printf("%s\n", token->value);
	i = 0;
	closed = 1;
	while (token->value[i])
	{
		q = '\0';
		if (token->value[i] == '\'' || token->value[i] == '"')
		{
			closed *= -1;
			if (token->value[i] == '"')
				q = token->value[i];
			else if (token->value[i] == '\'')
				q = token->value[i];
			while (token->value[++i])
			{
				if (token->value[i] == q)
				{
					closed *= -1;
					break ;
				}
			}
		}
		i++;
	}
	if (closed == -1 && q != '\0')
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

//j is the index to env str with var, or -1 if n/a, or 0 if its $? special case
int	var_status(char *str, char **env)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	if (str[0] == '_')
		return (-2);
	if (str[0] == '?')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == 0)
		return (-2);
	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(str, env[j], i) && env[j][i] == '=')
			return (j);
		// else if (ft_strncmp(str, "$?", 2))
		// {
		// 	printf("yoshi\n");
		// 	return (0);
		// }
		j++;
	}
	return (-1);
}

char	*expanded(t_shelgon *shelgon, char *line, char *tok_str, int index, int flag)
{
	int		i;
	int		j;
	char	*new;
	char	*trim_l;
	int		size;
	i = 0;
	
	if (flag)
	{	
		trim_l = ft_strchr(line, '=');
		if (!trim_l)
			return (NULL);
		trim_l++;
		while (line[i] && line[i] != '=')
			i++;
	}
	else
	{
		trim_l = ft_itoa(shelgon->status);
		i++;
	}
	if (!trim_l)
		return (NULL);
	size = ft_strlen(tok_str) + ft_strlen(trim_l) - i + 1;
	new = malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	ft_memset(new, 'a', size);
	new[size - 1] = '\0';
	//printf("%s\n", new);
	ft_strlcpy(new, tok_str, index);
	//printf("%s\n", new);
	//printf("%zu\n", ft_strlen(trim_l) + 1);
	ft_strlcat(new, trim_l, size);
	//printf("%s\n", new);
	// while (ft_isalnum(tok_str[i]) || tok_str[i] == '_')
	// 	i++;
	while (index + i-- > 0)
		tok_str++;
	ft_strlcat(new, tok_str, size);
	// while (tok_str[j])
	// {
	// 	if (j >= index)
	// 	{
	// 		while (line[i])
	// 		{
	// 			new[j] = line[i];
	// 			i++;
	// 			j++;
	// 		}
	// 	}
	// 	new[j] = tok_str[j];
	// 	j++;
	// }
	// new[j] = '\0';
	//printf("%s\n", new);
	if (!flag)
		free(trim_l);
	return (new);
	
}

char	*ft_rm_substr(char *str, int start, int end)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (ft_strlen(str) - (end - start) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i < start || i > end)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

//might remove a token if it cant expand instead we shall see
void	expansion(t_token *token, t_shelgon *shelgon)
{
	int		i;
	int		j;
	char	**env;
	char	*new_val;
	int		expand;

	env = shelgon->envr;
	j = 0;
	expand = 1;
	while (token->value[j])
	{
		if (token->value[j] == '\'')
		{
			//printf("haha\n");
			expand *= -1;
			//printf("%i\n", expand);
		}
		else if (token->value[j] == '$' && expand > 0)
		{
			// printf("oop\n");
			//printf("%s\n", &token->value[j + 1]);
			i = var_status(&token->value[j + 1], env);
			if (i == -1)
			{
				i = j + 1;
				while(ft_isalnum(token->value[i]) || token->value[i] == '_')
					i++;
				new_val = ft_rm_substr(token->value, j, i - 1);
				//printf("%s\n", new_val);
				free(token->value);
				token->value = new_val;
				j--;
			}
			else if (i >= 0)
			{
				//printf("str index: %c\n", 		token->value[j + 1])
				new_val = expanded(shelgon, env[i], token->value, j + 1, i);
				if (!new_val)
					return ;
				free(token->value);
				token->value = new_val;
			}
		}
		j++;
		//printf("%c\n", token->value[j]);
	}
}

// //might remove a token if it cant expand instead we shall see
// void	expansion(t_token *token, t_shelgon *shelgon)
// {
// 	int		i;
// 	int		j;
// 	char	**env;
// 	char	*new_val;
// 	char	*temp;
// 	int		expand;

// 	env = shelgon->envr;
// 	j = 0;
// 	expand = 1;
// 	while (token->value[j])
// 	{
// 		if (token->value[j] == '\'')
// 			expand *= -1;
// 		else if (token->value[j] == '$' && expand)
// 		{
// 			i = 0;
// 			while (env[i])
// 			{
// 				temp = &token->value[j + 1];
// 				if (!ft_strncmp(temp, env[i], ft_strlen(temp))
// 					&& env[i][ft_strlen(temp)] == '=')
// 				{
// 					new_val = malloc(sizeof(char)
// 							* (ft_strlen(env[i]) - ft_strlen(temp)));
// 					j = ft_strlen(temp);
// 					temp = &env[i][j + 1];
// 					ft_strlcpy(new_val, temp, ft_strlen(temp) + 1);
// 					free(token->value);
// 					token->value = new_val;
// 					return ;
// 				}
// 				i++;
// 			}
// 			free(token->value);
// 			token->value = malloc(sizeof(char) * 1);
// 			token->value[0] = '\0';
// 		}
// 		j++;
// 	}
// }

//print error message
int	handle_word(t_token *token, t_shelgon *shelgon)
{
	if (unclosed_quotes(token))
	{
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
		return (1);
	}
	// if (token->type != S_STR && !ft_strcmp(token->value, "$?"))
	// {
	// 	free(token->value);
	// 	token->value = ft_itoa(shelgon->status);
	// }
	// else if (token->type != S_STR)
	// {
	expansion(token, shelgon);
	// printf("%s\n", token->value);
	// }
	rm_quotes(token);
	//rm_quotes(token);
	//printf("%s\n", token->value);
	token->type = WORD;
	return (0);
}



