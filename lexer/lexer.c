/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:44 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/17 16:41:44 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//str_token with only WORD
int	str_token(t_token *token, int type, char *line, int i)
{
	int		j;
	int		quote;
	char	*new_line;

	if (line[i] == '"')
		quote = 2;
	else if (line[i] == '\'')
		quote = 1;
	else
		quote = 0;
	token->type = WORD;
	j = i + 1;
	if (quote == 2)
	{
		while (line[j] && line[j] != '"')
			j++;
		j++;
	}
	if (quote == 1)
	{
		while (line[j] && line[j] != '\'')
			j++;
		j++;
	}
	if (quote == 0)
	{
		j = i;
		while (line[j] && line[j] != ' ' && line[j]
			!= '|' && line[j] != '<' && line[j] != '>')
			j++;
		{
			token->value = ft_substr(line, i, j - i);
		}
	}
	else
		token->value = ft_substr(line, i, j - i);
	if (quote == 2 || quote == 1)
		return (j + 1);
	else
		return (j);
}

int	redirect_token(t_token *token, char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		token->type = REDIR_DELIMIT;
		return (i + 2);
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		token->type = REDIR_APP;
		return (i + 2);
	}
	else if (line[i] == '>')
	{
		token->type = REDIR_OUT;
		return (i + 1);
	}
	else if (line[i] == '<')
	{
		token->type = REDIR_IN;
		return (i + 1);
	}
	return (0);
}

//check for other whitespaces
int	env_token(t_token *token, char *line, int i)
{
	int	j;

	j = i + 1;
	token->type = ENV;
	while (line[j] && line[j] != '|' && line[j] != '<' && line[j] != '>')
		j++;
	token->value = ft_substr(line, i + 1, j - i - 1);
	while (line[j] && line[j] != ' ')
		j++;
	return (j);
}

t_token	*tokenize(char *line, t_shelgon *shelgon)
{
	int		i;
	t_token	*token;
	t_token	*head;

	i = 0;
	head = NULL;
	while (line && line[i])
	{
		token = ft_new_token();
		while (line[i] == ' ')
			i++;
		if (line[i] == '<' || line[i] == '>')
			i = redirect_token(token, line, i);
		else if (line[i] == '|')
		{
			token->type = PIPE;
			i++;
		}
		else if (line[i])
		{
			i = str_token(token, WORD, line, i);
			if (handle_word(token, shelgon))
				return (NULL);
		}
		ft_tokenadd_back(&head, token);
	}
	token = ft_new_token();
	token->type = END;
	ft_tokenadd_back(&head, token);
	head->prev = token;
	return (head);
}
