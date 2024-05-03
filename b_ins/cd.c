/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:02 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/03 17:41:29 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*new_pwd(t_env *cursor, char *pwd, char *tmp)
{
	if (cursor && cursor->vr && cursor->cpy)
	{
		tmp = ft_strdup(cursor->vr);
		free(cursor->vr);
		free(cursor->cpy);
		cursor->vr = ft_strjoin("PWD=", pwd);
		cursor->cpy = ft_strjoin("PWD=", pwd);
	}
	return (tmp);
}

static void	new_old_pwd(t_env *cursor, char *tmp)
{
	if (cursor && cursor->vr && cursor->cpy)
	{
		free(cursor->vr);
		free(cursor->cpy);
		cursor->vr = ft_strjoin("OLDPWD=", tmp + 4);
		cursor->cpy = ft_strjoin("OLDPWD=", tmp + 4);
	}
}

static void	update_pwd(t_shelgon *shelgon)
{
	char	*tmp;
	char	*pwd;
	t_env	*head;
	t_env	*cursor;

	pwd = getcwd(NULL, 0);
	head = shelgon->env;
	cursor = head;
	while (cursor && cursor->vr)
	{
		if (cursor->vr && ft_strncmp(cursor->vr, "PWD=", 4) == 0)
			tmp = new_pwd(cursor, pwd, tmp);
		cursor = cursor->next;
	}
	cursor = head;
	while (cursor && cursor->vr)
	{
		if (cursor->vr && ft_strncmp(cursor->vr, "OLDPWD=", 7) == 0)
			new_old_pwd(cursor, tmp);
		cursor = cursor->next;
	}
	free(pwd);
	free(tmp);
}

void	cd(char **arg, int flg, t_shelgon *shelgon)
{
	if (arg[2])
	{
		ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: cd: ", 2);
		ft_putendl_fd("too many arguments", 2);
		shelgon->status = 1;
	}
	else if (chdir(arg[1]) != 0)
	{
		ft_putstr_fd("(╯°□ °)╯︵ ┻━┻: cd: ", 2);
		if (arg[1])
			ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		shelgon->status = 1;
	}
	else
		shelgon->status = 0;
	update_pwd(shelgon);
	if (flg)
		return ;
	free_all(shelgon, shelgon->exe, BTIN);
	exit (0);
}
