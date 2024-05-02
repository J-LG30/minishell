/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:17:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/02 16:29:29 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	parse_arg(char *str, t_shelgon *shell)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || !ft_isalpha(str[0]))
	{
		shell->status = 1;
		ft_putendl_fd("export: not a valid identifier", 2);
		return (0);
	}
	while (str[i])
	{
		if ((!(ft_isalnum(str[i])) && !(str[i] == '_') && !(str[i] == '='
				 && !(str[i] == '\"'))))
		{
			shell->status = 1;
			ft_putendl_fd("export: not a valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	change_arg(t_env *tmp, char *str)
{
	free(tmp->vr);
	free(tmp->cpy);
	tmp->vr = ft_strdup(str);
	tmp->cpy = ft_strdup(str);
	tmp->prnt = 1;
}

static int	args_exist(char *str, t_env *env)
{
	t_env	*tmp;
	t_env	*new;
	int		i;
	int		flg;

	i = 0;
	flg = 0;
	tmp = env;
	while (str[i] && str[i] != '=')
		i++;
	while (tmp)
	{
		if (tmp && ((ft_strncmp(str, tmp->cpy, i) == 0) && (str[i] == '='
					&& (tmp->cpy[i] == '=' || !tmp->cpy[i]))))
		{
			change_arg(tmp, str);
			return (0);
		}
		else if (tmp && ((ft_strncmp(str, tmp->cpy, i) == 0) && str[i] != '='
				&& ((tmp->cpy[i] == '=') || (tmp->cpy[i] == '\0'))))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static void	add_export(char **args, t_shelgon *shell)
{
	int	i;
	int	j;
	int	flg;

	i = 1;
	flg = 0;
	while (args[i])
	{
		j = -1;
		flg = 0;
		if (parse_arg(args[i], shell) && args_exist(args[i], shell->env))
		{
			while (++j < ft_strlen(args[i]))
			{
				if (args[i][j] == '=')
				{
					ms_addnode(&shell->env, args[i]);
					flg = 1;
				}
			}
			if (!flg)
				ms_addexp(&shell->env, args[i]);
		}
		i++;
	}
}

void	export(t_branch *cmds, t_shelgon *shell, int flg)
{
	if (!cmds->full_cmd[1])
		print_exp(shell);
	else
		add_export(cmds->full_cmd, shell);
	shell->status = 0;
	if (flg)
		return ;
	free_all(shell, shell->exe, BTIN);
	exit(0);
}
