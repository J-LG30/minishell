/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:48:58 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/25 15:05:49 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
volatile int	g_sig;

extern int	rl_on_new_line(void);
static void	save_env(char **envp, t_shelgon *shelgon)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i])
		i++;
	shelgon->envr = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	if (!shelgon->envr)
		return ;
	while (envp[i])
	{
		shelgon->envr[i] = ft_strdup(envp[i]);
		i++;
	}
	shelgon->envr[i] = NULL;
}

void	wait_loop(char **envp)
{
	char		*line;
	t_token 	*token;
	t_shelgon	*shelgon;
	t_token		*temp;

	shelgon = malloc(sizeof(t_shelgon) * 1);
	if (!shelgon)
		return ;
	shelgon->status = 0;
	save_env(envp, shelgon);
	shelgon->env = env(shelgon, envp, 1, 1);
	// for (int i = 0; shelgon->envr[i]; i++)
	// 	printf("env[%d] = %s\n", i, shelgon->envr[i]);
	while (1)
	{	
		set_prompt_handler();
		rl_on_new_line();
		line = readline("(੭｡╹▿╹｡)੭$ ");
		add_history(line);
		set_child_handler();
		if (!line)
		{
			printf("CTRL D?\n");
			free_shelgon(shelgon);
			exit(1);
		}
		if (ft_strlen(line) == 0)
		{
			free (line);
			continue ;
		}
		token = tokenize(line, shelgon);
		if (!token)
			continue ;
		temp = token;
		// while (temp)
		// {
		// 	printf("Token type: %i\n Token value: %s\n", temp->type, temp->value);
		// 	temp = temp->next;	
		// }
		shelgon->tree = NULL;
		shelgon->list_token = token;
		shelgon->current = token;
		shelgon->top_root = NULL;
		if (parser(token, &shelgon))
		{
			//print_tree(shelgon->tree);
			exeggutor(shelgon->tree, shelgon, shelgon->env);
			free_ast(shelgon->tree);
		}
		free_tokens(token);
	}
	free_shelgon(shelgon);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	wait_loop(envp);
}
