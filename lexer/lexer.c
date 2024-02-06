#include "../inc/minishell.h"

void	str_token(t_token *token, int type, char *line, int i)
{
	int	j;
	char quote;
	char *new_line;

	j = i + 1;
	if (type == D_STR)
		quote = '"';
	if (type = S_STR)
		quote = '\'';
	token->type = type;
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
		token->error = -1;
	token->value = ft_substr(line, i + 1, j - i - 1);
	//if (token->value == NULL)
		//do something
		//error management

}

void	redirect_token(t_token *token, char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		token->type = REDIR_DELIMIT;
	else if (line[i] == '>' && line[i + 1] == '>')
		token->type = REDIR_APP;
	else if (line[i] == '>')
		token->type = REDIR_OUT;
	else if (line[i] == '<')
		token->type = REDIR_IN;
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
		token = ft_new_token(NULL);
		while(line[i] == ' ')
			i++;
		if (line[i] == '"')
			str_token(token, D_STR, line, i);
		if (line[i] == '\'')
			str_token(token, S_STR, line, i);
		if (line[i] == '<' || line[i] == '>')
			redirect_token(token, line, i);
		if (line[i] == '|')
			token->type = PIPE;
		if (line[i] == '$')
			token->type = ENV;
	}
}
// t_token *lexer(char *line)
// {
// 	int i;
// 	int err_flag;
// 	t_token *token;
// 	t_token *head;

// 	i = 0;
// 	head = NULL;
// 	while (line[i])
// 	{
// 		while (line[i] && line[i] == ' ')
// 			i++;
// 		err_flag = -1;
// 		token = malloc(sizeof(t_token));
// 		if (!token)
// 			return (0);
// 		token->next = NULL;
// 		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
// 				token->type = OPERATOR;
// 		else if (line[i] == '\"')
// 		{
// 			token->type = D_STR;
// 			while (line[++i])
// 			{
// 				if (line[i] == '\"')
// 				{
// 					err_flag = 0;
// 					break ;
// 				}
// 			}
// 			if (err_flag == -1)
// 			{
// 				write (1, "invalid str", 11);
// 				exit (1);
// 			}
// 		}
// 		else
// 		{
// 			token->type = COMMAND;
// 			while (line[i] && line[i] != ' ')
// 				i++;
// 		}
// 		ft_tokenadd_back(&head, token);
// 	}
// 	token->next = NULL;
// 	return (head);
// }