/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:31:54 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/03 18:40:47 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	free_branch(t_branch *branch)
{
	t_branch	*cursor;
	int			i;

	if (!branch)
		return ;
	cursor = branch;
	while (branch)
	{
		if (cursor->full_cmd)
			free(cursor->full_cmd);
		if (cursor->pipe[0] > 2)
			close(cursor->pipe[0]);
		branch = branch->next;
		if (cursor)
			free(cursor);
		cursor = branch;
	}
	if (branch)
		free(branch);
}

void	free_exegg(t_exegg *exe)
{
	int	i;

	i = 0;
	if (!exe)
		return ;
	free_branch(exe->cmd);
	while (exe->cmdpath && exe->cmdpath[i])
	{
		free(exe->cmdpath[i]);
		i++;
	}
	if (exe->fd[0])
		close(exe->fd[0]);
	free(exe->cmdpath);
	free(exe);
}

void	dumb_env(t_shelgon *shelgon)
{
	char	*dumb_env[3];
	char	*temp;

	temp = getcwd(NULL, 0);
	dumb_env[0] = ft_strjoin("PWD=", temp);
	free(temp);
	dumb_env[1] = "SHLVL=1";
	dumb_env[2] = "PATH=/usr/bin/";
	shelgon->envr[0] = dumb_env[0];
	shelgon->envr[1] = dumb_env[1];
	shelgon->envr[2] = dumb_env[2];
	shelgon->envr[3] = NULL;
	shelgon->free = 0;
}

void	main_help(t_shelgon *shelgon, t_token *token)
{
	shelgon->tree = NULL;
	shelgon->list_token = token;
	shelgon->current = token;
	shelgon->top_root = NULL;
	shelgon->print_error = 0;
}

void	time_to_start(t_shelgon *shelgon, t_token *token)
{
	if (parser(token, &shelgon))
		exeggutor(shelgon->tree, shelgon, shelgon->env);
	else
		shelgon->status = 2;
	free_ast(shelgon->tree);
	free_tokens(token);
}
