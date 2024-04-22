/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:17:00 by davda-si          #+#    #+#             */
/*   Updated: 2024/04/22 15:15:37 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/minishell.h"
// /* 
// int	main(int ac, char **av, char **envp)
// {
// 	t_exp	*exp;
// 	int		i;
	
// 	(void)ac;
// 	exp = malloc(sizeof(t_exp));
// 	if (!exp)
// 		return (1);
// 	i = 0;
// 	exp = NULL;
// 	while (envp[i])
// 	{
// 		ms_addnode(&exp, envp[i]);
// 		i++;
// 	}
// 	if (!av[1])
// 		print_list_exp(&exp);
// 	else
// 	{
// 		if (check_equal(av[1]))
// 		{
// 			ms_addnode(&exp, av[1]);
// 			ms_addnode(&env, av[1]);
// 		}
// 		else
// 			ms_addnode(&exp, av[1]);
// 	}
// } */


// static void	sort_exp(t_shelgon *shell)
// {
// 	t_env	*tmp;
// 	char	*var_tmp;

// 	tmp = shell->env;
// 	while (tmp->next)
// 	{
// 		if (ft_strcmp(tmp->cpy, tmp->next->cpy) > 0)
// 		{
// 			var_tmp = tmp->cpy;
// 			tmp->cpy = tmp->next->cpy;
// 			tmp->next->cpy = var_tmp;
// 			tmp = shell->env;
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// }

// static void	print_exp(t_shelgon *shell)
// {
// 	t_env	*tmp;
// 	int		i;
// 	int		flg;

// 	sort_exp(shell);
// 	tmp = shell->env;
// 	while(tmp)
// 	{
// 		i = 0;
// 		flg = 0;
// 		ft_putstr_fd("declare -x ", 1);
// 		while (tmp->cpy[i])
// 		{
// 			if (tmp->cpy[i] == '=')
// 			{
// 				write(1, &tmp->cpy[i], 1);
// 				if (!flg)
// 					write(1, "\"", 1);
// 				flg = 1;
// 			} 
// 			else
// 				write(1, &tmp->cpy[i], 1);
// 			i++;
// 		}
// 		if (flg)
// 			write(1, "\"", 1);
// 		printf("\n");
// 		tmp = tmp->next;
// 	}
// }

// static int	parse_arg(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_isdigit(str[0]))
// 		return (0);
// 	while (str[i])
// 	{
// 		if ((!(ft_isalnum(str[i])) && !(str[i] == '_') && !(str[i] == '=')))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// /* static int	args_exist(char *str, t_env *env)
// {
// 	t_env	*tmp;
// 	t_env	*new;
// 	int		i;
// 	int		flg;

// 	tmp = env;
// 	i = 0;
// 	flg = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 			flg = 1;
// 		i++;
// 	}
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->vr, str, ft_strlen(str)) && flg)
// 		{
			
// 		}
// 	}
// } */

// static void	add_export(char **args, t_shelgon *shell)
// {
// 	int	i;
// 	int	j;
// 	int	flg;

// 	i = 1;
// 	flg = 0;
// 	while (args[i])
// 	{
// 		j = -1;
// 		flg = 0;
// 		if (parse_arg(args[i]) /* args_exist(args[i], shell->env) */)
// 		{
// 			while (++j < ft_strlen(args[i]))
// 			{
// 				if (args[i][j] == '=')
// 				{
// 					ms_addnode(&shell->env, args[i]);
// 					flg = 1;
// 				}
// 			}
// 			if (!flg)
// 				ms_addexp(&shell->env, args[i]);
// 		}
// 		i++;
// 	}
// }

// void	export(t_branch *cmds, t_shelgon *shell)
// {
// 	if (!cmds->full_cmd[1])
// 		print_exp(shell);
// 	else
// 		add_export(cmds->full_cmd, shell);
// 	exit(0);
// }

#include "../inc/minishell.h"

static void	sort_exp(t_shelgon *shell)
{
	t_env	*tmp;
	char	*var_tmp;

	tmp = shell->env;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->cpy, tmp->next->cpy) > 0)
		{
			var_tmp = tmp->cpy;
			tmp->cpy = tmp->next->cpy;
			tmp->next->cpy = var_tmp;
			tmp = shell->env;
		}
		else
			tmp = tmp->next;
	}
}

static void	print_exp(t_shelgon *shell)
{
	t_env	*tmp;
	int		i;
	int		flg;

	sort_exp(shell);
	tmp = shell->env;
	while(tmp)
	{
		i = 0;
		flg = 0;
		ft_putstr_fd("declare -x ", 1);
		while (tmp->cpy[i])
		{
			if (tmp->cpy[i] == '=')
			{
				write(1, &tmp->cpy[i], 1);
				if (!flg)
					write(1, "\"", 1);
				flg = 1;
			} 
			else
				write(1, &tmp->cpy[i], 1);
			i++;
		}
		if (flg)
			write(1, "\"", 1);
		printf("\n");
		tmp = tmp->next;
	}
}

static int	parse_arg(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if ((!(ft_isalnum(str[i])) && !(str[i] == '_') && !(str[i] == '=')))
			return (0);
		i++;
	}
	return (1);
}

/* static int	args_exist(char *str, t_env *env)
{
	t_env	*tmp;
	t_env	*new;
	int		i;
	int		flg;

	tmp = env;
	i = 0;
	flg = 0;
	while (str[i])
	{
		if (str[i] == '=')
			flg = 1;
		i++;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->vr, str, ft_strlen(str)) && flg)
		{
			
		}
	}
} */

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
		if (parse_arg(args[i]) /* args_exist(args[i], shell->env) */)
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

void	export(t_branch *cmds, t_shelgon *shell)
{
	if (!cmds->full_cmd[1])
		print_exp(shell);
	else
		add_export(cmds->full_cmd, shell);
	exit(0);
}