/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:36:32 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/01 17:34:08 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fst_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	t_ast	*temp;

	temp = tree;
	find_redir(cmds->ref, exe, cmds);
	if (check_dotslash(cmds->full_cmd[0]))
	{
		ft_putendl_fd("wtf", 2);
		execve(cmds->full_cmd[0], cmds->full_cmd, exe->pkcenter->envr);
	}
	if (((!cmds->next || cmds->next->ref->type != WORD) && !(temp && (temp->type == PIPE)) && exe->fd_out == exe->fd[1]))
	{
		exe->fd_out = STDOUT_FILENO;
		close(exe->fd[1]);
	}
	if (exe->fd_in != STDIN_FILENO)
		exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	if (exe->fd_out != STDOUT_FILENO)
		exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	if (exe->fd_in != STDIN_FILENO)
		close(exe->fd_in);
	if (exe->fd_out != STDOUT_FILENO)
		close(exe->fd_out);
	if (exe->dup_fd[0] < 0 || exe->dup_fd[1] < 0)
		ft_error(1, cmds, exe);
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
	}
}

void	lst_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	find_redir(cmds->ref, exe, cmds);
	if ((cmds->full_cmd[0][0] == '/' && cmds->full_cmd[0][1]) || (cmds->full_cmd[0][0] == '.' && cmds->full_cmd[0][1] == '/'))
		execve(cmds->full_cmd[0], cmds->full_cmd, exe->pkcenter->envr);
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
		ft_error(0, cmds, exe);
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
		run_btin(tree, exe, cmds, 0);
	else
	{
		execve(cmds->cmd, cmds->full_cmd, exe->pkcenter->envr);
		ft_putendl_fd("Error executing command", 2);
	}
	exit (1);
}

void	mid_child(t_ast *tree, t_exegg *exe, t_branch *cmds)
{
	find_redir(cmds->ref, exe, cmds);
	if (cmds->full_cmd[0][0] == '/' || (cmds->full_cmd[0][0] == '.' && cmds->full_cmd[0][1] == '/'))
		execve(cmds->full_cmd[0], cmds->full_cmd, exe->pkcenter->envr);
	exe->dup_fd[1] = dup2(exe->fd_in, STDIN_FILENO);
	exe->dup_fd[0] = dup2(exe->fd_out, STDOUT_FILENO);
	close(exe->fd_in);
	close(exe->fd_out);
	if (exe->dup_fd[0] < 0)
		ft_error(1, cmds, exe);
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
		ft_putendl_fd("Error executing command", 2);
	}
	exit (1);
}
