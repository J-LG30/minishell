/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:48:58 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/29 20:45:21 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

volatile int	g_sig;

extern int	rl_on_new_line(void);

static void	save_env(char **envp, t_shelgon *shelgon)
{
	int		i;
	char	*tmp;

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
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			tmp = ft_itoa(ft_atoi(envp[i] + 6) + 1);
			shelgon->envr[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		else
			shelgon->envr[i] = ft_strdup(envp[i]);
		i++;
	}
	shelgon->envr[i] = NULL;
}

static char	*wait_helper(t_shelgon *shel, char *l, t_token *tok, t_token *tmp)
{
	shel->tree = NULL;
	shel->list_token = NULL;
	set_prompt_handler();
	rl_on_new_line();
	l = readline("(੭｡╹▿╹｡)੭$ ");
	add_history(l);
	set_child_handler();
	if (!l)
	{
		free_all(shel, NULL, 1);
		exit(0);
	}
	return (l);
}

void	wait_loop(t_shelgon *shelgon, char *line, t_token *token, t_token *temp)
{
	while (1)
	{
		line = wait_helper(shelgon, line, token, temp);
		if (ft_strlen(line) == 0)
		{
			free (line);
			continue ;
		}
		token = tokenize(line, shelgon);
		if (!token)
			continue ;
		temp = token;
		shelgon->tree = NULL;
		shelgon->list_token = token;
		shelgon->current = token;
		shelgon->top_root = NULL;
		if (parser(token, &shelgon))
		{
			print_tree(shelgon->tree);
			exeggutor(shelgon->tree, shelgon, shelgon->env);
			free_ast(shelgon->tree);
		}
		free_tokens(token);
	}
	free_shelgon(shelgon);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*token;
	t_shelgon	*shelgon;
	t_token		*temp;

	shelgon = malloc(sizeof(t_shelgon) * 1);
	if (!shelgon)
		return (0);
	shelgon->status = 0;
	shelgon->exe = NULL;
	save_env(envp, shelgon);
	shelgon->env = env(shelgon, envp, 1, 1);
	(void)argc;
	(void)argv;
	wait_loop(shelgon, line, token, temp);
}
