/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:44 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/03 11:19:16 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	str_token(t_token *token, int type, char *line, int i)
{
	int		j;
	char	c;
	int		flag;

	token->type = WORD;
	j = i;
	flag = 0;
	c = '\0';
	while (line[j])
	{
		if (flag == 0 && (line[j] == '"' || line[j] == '\''))
		{
			flag = 1;
			c = line[j];
		}
		else if (flag == 1 && line[j] == c)
			flag = 0;
		if (flag == 0 && (line[j] == ' ' || line[j] == '|' || line[j] == '<'
				|| line[j] == '>'))
			break ;
		j++;
	}
	token->value = ft_substr(line, i, j - i);
	token->copy = ft_strdup(token->value);
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

void	add_last(t_token *head, t_shelgon *shelgon)
{
	t_token	*token;

	token = ft_new_token(shelgon);
	token->type = END;
	ft_tokenadd_back(&head, token);
	head->prev = token;
}

int	pipe_token(t_token *token, int i)
{
	token->type = PIPE;
	return (i + 1);
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
		token = ft_new_token(shelgon);
		while (line[i] == ' ')
			i++;
		if (line[i] == '<' || line[i] == '>')
			i = redirect_token(token, line, i);
		else if (line[i] == '|')
			i = pipe_token(token, i);
		else if (line[i])
		{
			i = str_token(token, WORD, line, i);
			if (handle_word(token, shelgon, head))
				return (NULL);
		}
		ft_tokenadd_back(&head, token);
	}
	add_last(head, shelgon);
	return (check_tokens(head, shelgon));
}
