/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:22:16 by davda-si          #+#    #+#             */
/*   Updated: 2024/05/04 20:12:54 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tokens_char(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

static void	link_tokens(t_token *token, t_token *new, t_token *subhead)
{
	token->next->prev = new;
	new->next = token->next;
	subhead->prev = token;
	token->next = subhead;
}

int	token_loop(char **tokens, t_shelgon *shelgon, t_token *token)
{
	int		i;
	t_token	*subhead;
	t_token	*new;

	i = 1;
	subhead = NULL;
	while (tokens[i])
	{
		new = ft_new_token(shelgon);
		if (!new)
		{
			free_tokens_char(tokens);
			return (1);
		}
		new->type = WORD;
		new->value = ft_strdup(tokens[i]);
		new->copy = ft_strdup(new->value);
		ft_tokenadd_back(&subhead, new);
		handle_word(new, shelgon, token);
		i++;
	}
	free_tokens_char(tokens);
	link_tokens(token, new, subhead);
	return (0);
}

void	token_help(char **tokens)
{
	free(tokens[0]);
	free(tokens);
	return ;
}

int	var_only_one(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i] && (s[i] == ' ' || s[i] != '\t' || s[i] != '\n'))
		i++;
	if (!s[i])
		return (1);
	while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
		i++;
	if (!s[i])
		return (1);
	while (s[i] && (s[i] == ' ' || s[i] != '\t' || s[i] != '\n'))
		i++;
	if (!s[i])
		return (1);
	if (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
		return (0);
	return (0);
}
