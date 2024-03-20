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
		line = readline("\U0001F975 minishell > ");
		if (!line)
			exit(1);
		if (ft_strlen(line) == 0)
		{
			free (line);
			continue ;
		}
		token = tokenize(line);
		shelgon->tree = NULL;
		shelgon->list_token = token;
		shelgon->current = token;
		shelgon->top_root = NULL;
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
			// printf("\n\n");
			// printf("TYPE: %d, VALUE: %s\n", shelgon->tree->type, shelgon->tree->value);
			// printf("TYPE: %d, VALUE: %s\n", shelgon->tree->right->type, shelgon->tree->right->value);
			// if (shelgon->tree->right->right == NULL)
			// 	printf("NULL\n");
			// else{
			// 	printf("TYPE: %d, VALUE: %s\n", shelgon->tree->right->left->type, shelgon->tree->right->left->value);
			// 	printf("TYPE: %d, VALUE: %s\n", shelgon->tree->right->right->type, shelgon->tree->right->right->value);
			// }
			// if (shelgon->tree->left == NULL)
			// 	printf("NULL\n");
			//exit(0);
			print_tree(shelgon->tree);
			check_input(line, env);
			add_history(line);
			free_ast(shelgon->tree);
		}
		else
			printf("minishell: error with parsing\n");
		free_tokens(token);
	}
	if (token)
		free_tokens(token);
	free(shelgon);
}

int	main(int argc, char **argv, char **env)
{
	wait_loop(env);
}