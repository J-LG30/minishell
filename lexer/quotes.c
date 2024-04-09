/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:45:36 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/09 17:58:20 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unclosed_quotes(t_token *token)
{
	int	flag;
	int	i;
	int	closed;

	i = 0;
	closed = -1;
	//printf("%s\n", token->value);
	if (token->value[0] != '\'' && token->value[0] != '"')
		return (0);
	while (token->value[i]
		&& (token->value[i] != '\'' && token->value[i] != '"'))
	{
		i++;
	}
	if (token->value[i] == '"')
		token->type = D_STR;
	else if (token->value[i] == '\'')
		token->type = S_STR;
	while (token->value[++i])
	{
		if (token->type == D_STR && token->value[i] == '"')
			closed *= -1;
		else if (token->type == S_STR && token->value[i] == '\'')
			closed *= -1;
	}
	if (closed == -1 && (token->type == D_STR || token->type == S_STR))
		return (1);
	return (0);
}

void	rm_quotes(t_token *token)
{
	char	*new_val;
	
	if (token->type == D_STR)
		new_val = ft_strtrim(token->value, "\"");
	else if (token->type == S_STR)
		new_val = ft_strtrim(token->value, "'");
	if (!new_val)
		return ; //MALLOC error
	free(token->value);
	token->value = new_val;
}

//might remove a token if it cant expand instead we shall see
void	expansion(t_token *token, t_shelgon *shelgon)
{
	int		i;
	int		j;
	char 	**env;
	char	*new_val;
	char	*temp;

	env = shelgon->envr;
	//printf("1\n");
	j = 0;
	while (token->value[j])
	{
		if (token->value[j] == '$')
		{
			i = 0;
			//printf("3\n");
			while (env[i])
			{
				temp = &token->value[j + 1];
				//printf("4\n");
				//printf("%s\n", temp);
				//printf("%s\n", env[i]);
				//printf("%c\n", env[i][ft_strlen(temp)]);
				if (!ft_strncmp(temp, env[i], ft_strlen(temp)) && env[i][ft_strlen(temp)] == '=')
				{
					//printf("5\n");
					new_val = malloc(sizeof(char) * (ft_strlen(env[i]) - ft_strlen(temp)));
					//printf("6\n");
					j = ft_strlen(temp);
					temp = &env[i][j + 1];
					ft_strlcpy(new_val, temp, ft_strlen(temp) + 1);
					free(token->value);
					//printf("9\n");
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

int	handle_word(t_token *token, t_shelgon *shelgon)
{
	printf("%s\n", token->value);
	if (unclosed_quotes(token))
	{
		printf("Error: Unclosed quotes\n"); //print error message
		return (1);
	}
	//printf("%s\n", token->value);
	if (token->type != WORD)
		rm_quotes(token);
	//printf("%s\n", token->value);
	if (token->type != S_STR)
		expansion(token, shelgon);
	token->type = WORD;
	return (0);
}



