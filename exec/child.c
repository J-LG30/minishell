/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:36:32 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/26 20:11:07 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*try_cmd(char *cargs, char **cpath)
{
	char	*temp;
	char	*com;
	int		i;

	i = 0;
	com = NULL;
	while (cpath[i])
	{
		/* ft_putendl_fd("trying the cmd", 2);
		ft_putendl_fd("cpath[i]", 2);
		ft_putendl_fd(cpath[i], 2); */
		temp = ft_strjoin(cpath[i], "/");
		/* ft_putendl_fd("temp", 2);
		ft_putendl_fd(temp, 2);
		ft_putendl_fd("cargs", 2);
		ft_putendl_fd(cargs, 2); */
		com = ft_strjoin(temp, cargs);
		/* ft_putendl_fd("com", 2);
		ft_putendl_fd(com, 2); */
		free(temp);
		if (access(com, F_OK) == 0)
			return (com);
		free(com);
		i++;
	}
	return (NULL);
}

void	fst_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	t_ast	*temp;

	temp = tree;
	find_redir(cmds->ref, exe, cmds);
	ft_putendl_fd("1", 2);
	if (cmds->full_cmd[0][0] == '/' || (cmds->full_cmd[0][0] == '.' && cmds->full_cmd[0][1] == '/'))
		execve(cmds->full_cmd[0], cmds->full_cmd, exe->pkcenter->envr);
	ft_putendl_fd("2", 2);
	if (((!cmds->next || cmds->next->ref->type != WORD) && !(temp && (temp->type == PIPE)) && exe->fd_out == exe->fd[1]))
	{
		exe->fd_out = STDOUT_FILENO;
		close(exe->fd[1]);
	}
	ft_putendl_fd("3", 2);
	if (exe->fd_in != STDIN_FILENO)
		exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	if (exe->fd_out != STDOUT_FILENO)
		exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	if (exe->fd_in != STDIN_FILENO)
		close(exe->fd_in);
	if (exe->fd_out != STDOUT_FILENO)
		close(exe->fd_out);
	if (exe->dup_fd[0] < 0 || exe->dup_fd[1] < 0)
		ft_error(1, exe);
	if (cmds->ref && cmds->ref->type == WORD && !(is_btin(cmds->full_cmd[0])))
	{
		cmds->cmd = try_cmd(cmds->full_cmd[0], exe->cmdpath);
		if (!cmds->cmd)
		{
			ft_putendl_fd("command not found", 2);
			free_all(exe->pkcenter, exe, WRONG_CMD);
			exit (127);
		}
	}
	if (is_btin(cmds->full_cmd[0]))
		run_btin(tree, exe, cmds, 0);
	else
	{
		execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
		ft_putendl_fd("5", 2);
		ft_putendl_fd("Error executing command", 2);
		//free_all(exe->pkcenter, exe, WRONG_CMD);
	}
}

void	lst_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	find_redir(cmds->ref, exe, cmds);
	if (exe->fd_out == exe->fd[1] || (cmds->next && cmds->next->ref->type != WORD))
		exe->fd_out = STDOUT_FILENO;
	if (exe->fd_out != STDOUT_FILENO)
		exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	if (exe->fd_in != STDIN_FILENO)
		close(exe->fd_in);
	close(exe->fd[1]);
	close(exe->fd[0]);
	if (exe->fd_out != STDOUT_FILENO)
		close(exe->fd_out);
	if (exe->dup_fd[0] < 0)
	{
		ft_putendl_fd("end\n", 2);
		ft_error(0, exe);
	}
	if (cmds->ref && cmds->ref->type == WORD && !(is_btin(cmds->full_cmd[0])))
	{
		cmds->cmd = try_cmd(cmds->full_cmd[0], exe->cmdpath);
		if (!cmds->cmd)
		{
			ft_putendl_fd("command not found", 2);
			free_all(exe->pkcenter, exe, WRONG_CMD);
			exit (127);
		}
	}
	if (is_btin(cmds->full_cmd[0]))
	{
		run_btin(tree, exe, cmds, 0);
		//free_all(exe->pkcenter, exe, WRONG_CMD);
	}
	else
	{
		execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
		ft_putendl_fd("Error executing command", 2);
		//free_all(exe->pkcenter, exe, WRONG_CMD);
	}
	exit (1);
}

void	mid_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	find_redir(cmds->ref, exe, cmds);
	exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	close(exe->fd_in);
	close(exe->fd_out);
	if (exe->dup_fd[0] < 0)
		ft_error(1, exe);
	if (cmds->ref && cmds->ref->type == WORD && !(is_btin(cmds->full_cmd[0])))
	{
		cmds->cmd = try_cmd(cmds->full_cmd[0], exe->cmdpath);
		if (!cmds->cmd)
		{
			ft_putendl_fd("command not found", 2);
			free_all(exe->pkcenter, exe, WRONG_CMD);
			exit (127);
		}
	}
	if (is_btin(cmds->full_cmd[0]))
	{
		run_btin(tree, exe, cmds, 0);
		//free_all(exe->pkcenter, exe, WRONG_CMD);
	}
	else
	{
		execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
		ft_putendl_fd("Error executing command", 2);
		//free_all(exe->pkcenter, exe, WRONG_CMD);
	}
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
	//new = malloc(sizeof(t_branch) * 1);
	new = ft_calloc(1, sizeof(t_branch));
	if (!new)
		return (NULL);
	if (temp->type == WORD)
	{
		new->cmd = temp->value;
		while (temp->right && temp->right->type == WORD)
		{
			j++;
			temp = temp->right;
		}
		new->full_cmd = (char **)malloc(sizeof(char *) * (j + 1));
		if (!new->full_cmd)
			return (NULL);
		temp = tree;
		if (new->cmd)
			new->full_cmd[0] = new->cmd;
		new->ref = temp;
		while (temp->right && temp->right->type == WORD)
		{
			i++;
			new->full_cmd[i] = temp->right->value;
			temp = temp->right;
		}
		new->full_cmd[i + 1] = NULL;
		new->pipe[0] = 0;
	}
	new->full_cmd[i + 1] = NULL;
	return (new);
}

int	get_cmd(t_ast *tree, t_branch **cmds, t_exegg *exe)
{
	t_ast		*temp;
	t_branch	*cur;
	t_branch	*last;
	int			no_cmds;
	static int	i = 0;

	temp = tree;
	no_cmds = 1;
	cur = NULL;
	while (temp)
	{
		if (temp && temp->type == WORD)
		{
			cur = node_cmd(temp);
			if (!cur)
				return (0);
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
			i++;
			no_cmds = 0;
		}
		else if (temp && temp->type == REDIR_DELIMIT)
		{
			cur = ft_calloc(1, sizeof(t_branch));
			if (!cur)
				return (0);
			ft_memset(cur, 0, 0);
			cur->pipe[0] = ft_heredoc(temp);
			set_child_handler();
			cur->ref = temp;
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
	if (temp && temp->type != PIPE && temp->type != WORD && temp->type != REDIR_DELIMIT)
	{
		// cur = malloc(sizeof(t_branch) * 1);
		cur = ft_calloc(1, sizeof(t_branch));
		if (!cur)
			return (0);
		ft_memset(cur, 0, 0);
		cur->ref = temp;
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
	if (cur)
		cur->next = NULL;
	temp = tree;
	if (temp && temp->type == PIPE)
		get_cmd(temp->right, cmds, exe);
	return (no_cmds);
}
