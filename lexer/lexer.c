#include "../inc/minishell.h"

int	str_token(t_token *token, int type, char *line, int i)
{
	int	j;
	char quote;
	char *new_line;

	j = i + 1;
	if (type == D_STR)
		quote = '"';
	if (type == S_STR)
		quote = '\'';
	token->type = type;
	if (type == D_STR || type == S_STR)
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
		while (line[j] && line[j] != ' ')
			j++;
		token->value = ft_substr(line, i - 1, j - i + 1);
	}
	else
		token->value = ft_substr(line, i + 1, j - i - 1);
	//if (token->value == NULL)
		//do something
		//error management
	return (j + 1);

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
		if (line[i] == '"')
			i = str_token(token, D_STR, line, i);
		else if (line[i] == '\'')
			i = str_token(token, S_STR, line, i);
		else if (line[i] == '<' || line[i] == '>')
			i = redirect_token(token, line, i);
		else if (line[i++] == '|')
			token->type = PIPE;
		else if (line[i] == '$')
		{
			token->type = ENV;
			while (line[i] != ' ')
			i++;
		}
		else
			i = str_token(token, WORD, line, i);
		ft_tokenadd_back(&head, token);	
	}
	token = ft_new_token();
	token->type = END;
	ft_tokenadd_back(&head, token);
	return (head);
}