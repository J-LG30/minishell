#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*arr;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	arr = NULL;
	while(env[i])
	{
		ms_addnode(&arr, env[i]);
		i++;
	}
	print_list(arr);
}

