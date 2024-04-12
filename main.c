/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:48:58 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/12 19:06:13 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
int	g_sig;

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

void	wait_loop(char **env)
{
	char		*line;
	t_token 	*token;
	t_shelgon	*shelgon;
	t_token		*temp;

	shelgon = malloc(sizeof(t_shelgon) * 1);
	if (!shelgon)
		return ;
	save_env(env, shelgon);
	// for (int i = 0; shelgon->envr[i]; i++)
	// 	printf("env[%d] = %s\n", i, shelgon->envr[i]);
	while (1)
	{
		rl_on_new_line();
		line = readline("\U0001F975 minishell > ");
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			free(line);
			continue ;
		}
		if (!line)
			exit(1);
		if (ft_strlen(line) == 0)
		{
			free (line);
			continue ;
		}
		token = tokenize(line, shelgon);
		if (!token)
			continue ;
		temp = token;
		while (temp)
		{
			printf("Token type: %i\n Token value: %s\n", temp->type, temp->value);
			temp = temp->next;	
		}
		shelgon->tree = NULL;
		shelgon->list_token = token;
		shelgon->current = token;
		shelgon->top_root = NULL;
		parser(token, &shelgon);
		if (shelgon->tree)
		{
			print_tree(shelgon->tree);
			exeggutor(shelgon->tree, shelgon);
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
	struct sigaction	sa;
	
	sa.sa_handler = &sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	
	(void)argc;
	(void)argv;
	wait_loop(env);
}
