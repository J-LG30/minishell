#include "minishell.h"

void	execute_command(char *command, char **env)
{
    pid_t pid = fork();

    if (pid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    } 
	else if (pid == 0)
	{
        // Child process
        char *args[] = {command, NULL};
        if (execve(command, args, env) == -1)
		{
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } 
	else
	{
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}