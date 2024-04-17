/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:45:36 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/17 16:46:25 by jle-goff         ###   ########.fr       */
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

//MALLOC error at return
void	rm_quotes(t_token *token)
{
	char	*new_val;

	if (token->type == D_STR)
		new_val = ft_strtrim(token->value, "\"");
	else if (token->type == S_STR)
		new_val = ft_strtrim(token->value, "'");
	if (!new_val)
		return ;
	free(token->value);
	token->value = new_val;
}

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
	printf("%s\n", token->value);
	if (unclosed_quotes(token))
	{
		printf("Error: Unclosed quotes\n");
		return (1);
	}
	if (token->type != WORD)
		rm_quotes(token);
	if (token->type != S_STR && !ft_strcmp(token->value, "$?"))
	{
		free(token->value);
		token->value = ft_itoa(shelgon->status);
	}
	else if (token->type != S_STR)
		expansion(token, shelgon);
	token->type = WORD;
	return (0);
}
