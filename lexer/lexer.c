/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:44 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/03 17:00:08 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	unclosed_quotes(t_token *token)
// {
// 	int	flag;

// 	flag = 0;
// 	if (token->value)
// }

//str_token with only WORD
int	str_token(t_token *token, int type, char *line, int i)
{
	int	j;
	char quote;
	char *new_line;

	j = i + 1;
	if (line[0] == '"')
		quote = '"';
	else if (line[0] == '\'')
		quote = '\'';
	else
		quote = 0;
	token->type = type;
	if (quote == '"' || quote == '\'')
	{
		while (line[j])
		{
			if (line[j] == quote)
			{
				token->error = 0;
				break ;
			}
			j++;
		}
		if (token->error != 0)
			token->error = 1;
	}
	if (type == WORD)
	{
		j = i;
		while (line[j] && line[j] != ' ' && line[j] != '|' && line[j] != '<' && line[j] != '>')
			j++;
		//printf("oh%cgod\n", line[j]);
		token->value = ft_substr(line, i, j - i);
		//printf("%c\n", line[j]);
		return (j);
	}
	else
	{
		token->value = ft_substr(line, i + 1, j - i - 1);
		return (j + 1);
	}
	//if (token->value == NULL)
		//do something
		//error management

}

//str_token that has WORD D_STR AND S_STR
// int	str_token(t_token *token, int type, char *line, int i)
// {
// 	int	j;
// 	char quote;
// 	char *new_line;

// 	j = i + 1;
// 	if (type == D_STR)
// 		quote = '"';
// 	if (type == S_STR)
// 		quote = '\'';
// 	token->type = type;
// 	if (type == D_STR || type == S_STR)
// 	{
// 		while (line[j])
// 		{
// 			if (line[j] == quote)
// 			{
// 				token->error = 0;
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (token->error != 0)
// 			token->error = 1;
// 	}
// 	if (type == WORD)
// 	{
// 		j = i;
// 		while (line[j] && line[j] != ' ' && line[j] != '|' && line[j] != '<' && line[j] != '>')
// 			j++;
// 		//printf("oh%cgod\n", line[j]);
// 		token->value = ft_substr(line, i, j - i);
// 		//printf("%c\n", line[j]);
// 		return (j);
// 	}
// 	else
// 	{
// 		token->value = ft_substr(line, i + 1, j - i - 1);
// 		return (j + 1);
// 	}
// 	//if (token->value == NULL)
// 		//do something
// 		//error management

// }

int	redirect_token(t_token *token, char *line, int i)
{
	int	j;

	if (line[i] == '<' && line[i + 1] == '<')
	{
		token->type = REDIR_DELIMIT;
		j = i + 2;
		return (i + 2);
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		token->type = REDIR_APP;
		j = i + 2;
		return (i + 2);
	}
	else if (line[i] == '>')
	{
		token->type = REDIR_OUT;
		j = i + 1;
		return (i + 1);
	}
	else if (line[i] == '<')
	{
		token->type = REDIR_IN;
		j = i + 1;
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

//version of tokenizer with only word tokens for all types of words(w or w/o quotes)
t_token *tokenize(char *line)
{
	int	i;
	t_token	*token;
	t_token	*head;

	i = 0;
	head = NULL;
	while (line[i])
	{
		token = ft_new_token();
		while(line[i] == ' ')
			i++;
		if (line[i] == '<' || line[i] == '>')
			i = redirect_token(token, line, i);
		else if (line[i] == '|')
		{
			token->type = PIPE;
			i++;
		}
		// else if (line[i] == '$')
		// 	i = env_token(token, line, i);
		else
			i = str_token(token, WORD, line, i);
		ft_tokenadd_back(&head, token);	
	}
	token = ft_new_token();
	token->type = END;
	ft_tokenadd_back(&head, token);
	head->prev = token;
	return (head);
}

//version of tokenizer with word d_str and s_str tokens
// t_token *tokenize(char *line)
// {
// 	int	i;
// 	t_token	*token;
// 	t_token	*head;

// 	i = 0;
// 	head = NULL;
// 	while (line[i])
// 	{
// 		//printf("%c\n", line[i]);
// 		token = ft_new_token();
// 		while(line[i] == ' ')
// 			i++;
// 		if (line[i] == '"')
// 			i = str_token(token, D_STR, line, i);
// 		else if (line[i] == '\'')
// 			i = str_token(token, S_STR, line, i);
// 		else if (line[i] == '<' || line[i] == '>')
// 			i = redirect_token(token, line, i);
// 		else if (line[i] == '|')
// 		{
// 			token->type = PIPE;
// 			i++;
// 		}
// 		else if (line[i] == '$')
// 			i = env_token(token, line, i);
// 		else
// 			i = str_token(token, WORD, line, i);
// 		ft_tokenadd_back(&head, token);	
// 	}
// 	token = ft_new_token();
// 	token->type = END;
// 	ft_tokenadd_back(&head, token);
// 	head->prev = token;
// 	return (head);
// }