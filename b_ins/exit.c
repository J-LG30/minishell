/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:14:10 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/07 15:11:55 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

__int64_t	ft_mod_atoi(const char *str)
{
	long long	i;
	int			sign;
	__int64_t	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	is_numeric_exit(char **full_cmd, t_shelgon *shelgon)
{
	__int64_t	i;
	int			flag;

	i = 0;
	flag = 0;
	if (!full_cmd[1] || !full_cmd[1][0])
		flag = 1;
	if ((full_cmd[1][0] == '+' || full_cmd[1][0] == '-') && !full_cmd[1][1])
		flag = 1;
	else
	{
		while (full_cmd[1][i] && full_cmd[1][i] == ' ')
			i++;
		if (!full_cmd[1][i])
			flag = 1;
		i = ft_mod_atoi(full_cmd[1]);
		if (i == -1 && full_cmd[1][2])
			flag = 1;
	}
	if (flag == 1)
	{
		print_err_msg(full_cmd, shelgon);
		return (2);
	}
	return (0);
}

int	too_many_args(char **full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("(╯°□ °)╯︵ ┻━┻: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	check_error(char **full_cmd, t_shelgon *shelgon)
{
	int		i;

	i = 0;
	if (is_numeric_exit(full_cmd, shelgon) == 2)
		return (2);
	if (full_cmd[1][0] == '+' || full_cmd[1][0] == '-')
		i++;
	while (full_cmd[1] && full_cmd[1][i])
	{
		if (!ft_isdigit(full_cmd[1][i]) && full_cmd[1][i] != ' ')
		{
			print_err_msg(full_cmd, shelgon);
			shelgon->status = 2;
			return (2);
		}
		i++;
	}
	if (too_many_args(full_cmd))
	{
		shelgon->status = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(t_shelgon *shelgon, t_branch *cmds, t_exegg *exe, int flg)
{
	char	**full_cmd;
	int		status;

	full_cmd = cmds->full_cmd;
	if (!full_cmd[1])
	{
		status = shelgon->status;
		ft_putendl_fd("exit (¬_¬)ﾉ", 1);
	}
	else
	{
		status = check_error(full_cmd, shelgon);
		if (status == 1 && flg == 1)
			return ;
		else if (status == 1 && flg == 0)
			exit_err(shelgon);
	}
	if (status != 2 && status != 1 && full_cmd[1])
	{
		status = ft_mod_atoi(full_cmd[1]);
		if (status < 0)
			status += 256;
		ft_putendl_fd("exit (¬_¬)ﾉ", 1);
	}
	finish_ex(exe, shelgon, status);
}
