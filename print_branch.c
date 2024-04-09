#include "inc/minishell.h"

void	print_branch(t_branch *branch)
{
	t_branch	*temp;
	int			i;

	printf("ello\n");
	if (branch)
	{
		printf("1\n");
		temp = branch;
		while (temp)
		{
			printf("2\n");
			printf("Command of branch: %s", temp->cmd);
			i = 0;
			printf("Full command of branch:\n");
			while (temp->full_cmd && temp->full_cmd[i])
			{
				printf("%s->", temp->full_cmd[i]);
				i++;
			}
			temp = temp->next;
		}
	}
}