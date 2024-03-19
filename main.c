#include "inc/minishell.h"

void	check_input(char *line, char ** env)
{
	if (ft_strncmp(line, "exit", 4) == 0
		|| ft_strncmp(line, "Exit", 4) == 0)
		exit (0);
	else
		execute_command(line, env);
}
void	wait_loop(char **env)
{
	char		*line;
	t_token 	*token;
	t_shelgon	*shelgon;

	shelgon = malloc(sizeof(t_shelgon) * 1);
	if (!shelgon)
		return ;
	while (1)
	{
		rl_on_new_line();
		printf("%s minishell > ", "\U0001F975");
		line = readline("");
		token = tokenize(line);
		shelgon->tree = NULL;
		shelgon->list_token = token;
		shelgon->current = token;
		shelgon->cmd_root = -1;
		// while (token)
		// {
		// 	printf("%i\n", token->type);
		// 	// if (token->error == 1)
		// 	// 	printf("Error with quotes\n");
		// 	if (token->value != NULL)
		// 		printf("%s\n", token->value);
		// 	if (token->value == NULL)
		// 		printf("null str value\n");
		// 	// if (token->type == PIPE)
		// 	// 	is_pipe = 1;
		// 	token = token->next;
		// }
		parser(token, &shelgon);
		if (shelgon->tree)
		{
			print_tree(shelgon->tree);
			check_input(line, env);
			add_history(line);
			free_ast(shelgon->tree);
		}
		else
			printf("minishell: error with parsing\n");
		free_tokens(token);
		free(shelgon);
	}
	if (token)
		free_tokens(token);
}

int	main(int argc, char **argv, char **env)
{
	wait_loop(env);
}