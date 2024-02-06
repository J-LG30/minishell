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
	char	*line;
	t_token *token;

	while (1)
	{
		rl_on_new_line();
		printf("%s minishell > ", "\U0001F975");
		line = readline("");
		token = tokenize(line);
		while (token != NULL)
		{
			printf("%i\n", token->type);
			if (token->error == 1)
				printf("Error with quotes\n");
			if (token->value != NULL)
				printf("%s\n", token->value);
			token = token->next;
		}
		check_input(line, env);
		add_history(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	wait_loop(env);
}