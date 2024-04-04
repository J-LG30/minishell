/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:36:32 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/04 15:01:41 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*try_cmd(char *cargs, char **cpath)
{
	char	*temp;
	char	*com;
	int		i;

	i = 0;
	com = NULL;
	while (cpath[i])
	{
		temp = ft_strjoin(cpath[i], "/");
		com = ft_strjoin(temp, cargs);
		free(temp);
		if (access(com, F_OK) == 0)
			return (com);
		free(com);
		i++;
	}
	return (NULL);
}
void	my_close(int fd)
{
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO)
		close(fd);
}

void	fst_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	find_redir(tree, exe, cmds);
	if (!cmds->next && exe->fd_out == exe->fd[1])
		exe->fd_out = STDOUT_FILENO;
	if (exe->fd_in != STDIN_FILENO)
		exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	if (exe->fd_out != STDOUT_FILENO)
		exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	if (exe->fd_in != STDIN_FILENO)
		my_close(exe->fd_in);
	if (exe->fd_out != STDOUT_FILENO)
		my_close(exe->fd_out);
	if (exe->dup_fd[0] < 0 || exe->dup_fd[1] < 0)
		ft_error(1, exe);
	cmds->cmd = try_cmd(cmds->full_cmd[0], exe->cmdpath);
	if (!cmds->cmd) 
	{
		//ft_freech(exe);
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
	// execve(cmds->cmd, &cmds->args, exe->pkcenter->envr);
	ft_putendl_fd("Error executing command", 2);
	//ft_freech(exe);
	//exit (1);
}

void	lst_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	find_redir(tree, exe, cmds);
	if (exe->fd_out != exe->fd[1])
		exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	my_close(exe->fd[1]);
	my_close(exe->fd_out);
	if (exe->dup_fd[0] < 0)
		ft_error(0, exe);
	cmds->cmd = try_cmd(cmds->full_cmd[0], exe->cmdpath);
	if (!cmds->cmd)
	{
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
	ft_putendl_fd("Error executing command", 2);
	exit (1);
}

void	mid_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	ft_putstr_fd("middle\n", 2);
	find_redir(tree, exe, cmds);
	exe->dup_fd[1] = dup2(exe->fd[0], STDIN_FILENO);
	exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	my_close(exe->fd[1]);
	my_close(exe->fd[0]);
	my_close(exe->fd_out);
	if (exe->dup_fd[0] < 0)
		ft_error(1, exe);
	cmds->cmd = try_cmd(cmds->full_cmd[0], exe->cmdpath);
	if (!cmds->cmd)
	{
		//ft_freech(exe);
		ft_putendl_fd("Error with the command", 2);
		exit (1);
	}
	execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
	ft_putendl_fd("Error executing command", 2);
	//ft_freech(exe);
	exit (1);
}

t_branch	*node_cmd(t_ast *tree)
{
	t_branch	*new;
	t_ast		*temp;
	int			i;
	int			j;

	i = 0;
	j = 1;
	temp = tree;
	new = malloc(sizeof(t_branch) * 1);
	if (!new)
		return (NULL);
	while (temp->right && temp->right->type == WORD)
	{
		j++;
		temp = temp->right;
	}
	new->full_cmd = (char **)malloc(sizeof(char *) * (j + 1));
	if (!new)
		return (NULL);
	//new->args = (char **)malloc(sizeof(char *) * j);
	temp = tree;
	new->cmd = temp->value;
	new->full_cmd[0] = new->cmd;
	if (tree->left && tree->left->type == REDIR_DELIMIT)
		new->pipe[0] = ft_heredoc(tree);
	new->ref = temp;
	while (temp->right && temp->right->type == WORD)
	{
		//new->args[i] = temp->right->value;
		i++;
		new->full_cmd[i] = temp->right->value;
		temp = temp->right;
	}
	//new->args[i] = NULL;
	new->full_cmd[i + 1] = NULL;
	return (new);
}

void	get_cmd(t_ast *tree, t_branch **cmds)
{
	t_ast		*temp;
	t_branch	*cur;
	t_branch	*last;

	temp = tree;
	while (temp)
	{
		if (temp && temp->type == WORD)
		{
			cur = node_cmd(temp);
			if (!cur)
				return ;
			if(!(*cmds))
			{
				*cmds = cur;
				cur->prev = NULL;
			}
			else
			{
				last = msh_lstlast(*cmds);
				last->next = cur;
				cur->prev = last;
			}
		}
			temp = temp->left;
	}
	cur->next = NULL;
	temp = tree;
	if (temp && temp->type == PIPE)
	{
		get_cmd(temp->right, cmds);
	}
}
