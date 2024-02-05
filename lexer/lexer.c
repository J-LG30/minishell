#include "../inc/minishell.h"

t_token *lexer(char *line)
{
	int i;
	int err_flag;
	t_token *token;
	t_token *head;

	i = 0;
	head = NULL;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		err_flag = -1;
		token = malloc(sizeof(t_token));
		if (!token)
			return (0);
		token->next = NULL;
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
				token->type = OPERATOR;
		else if (line[i] == '\"')
		{
			token->type = D_STR;
			while (line[++i])
			{
				if (line[i] == '\"')
				{
					err_flag = 0;
					break ;
				}
			}
			if (err_flag == -1)
			{
				write (1, "invalid str", 11);
				exit (1);
			}
		}
		else
		{
			token->type = COMMAND;
			while (line[i] && line[i] != ' ')
				i++;
		}
		ft_tokenadd_back(&head, token);
	}
	token->next = NULL;
	return (head);
}