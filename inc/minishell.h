/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:28 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/03 21:04:49 by davda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define WORD 1
#define S_STR 2
#define D_STR 3
#define S_CHAR 4
#define ENV 5
#define PIPE 6
#define REDIR_IN 7
#define REDIR_OUT 8
#define REDIR_APP 9
#define REDIR_DELIMIT 10
#define END 11

#define LEFT 20
#define RIGHT 21

typedef struct s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*vr;
}	t_env;

typedef struct s_branch
{
	struct s_branch	*prev;
	struct s_branch	*next;
	int				pipe[1];
	char			*cmd;
	char			**args;
	char			**full_cmd;
	struct s_ast	*ref;
}	t_branch;

typedef struct s_exegg
{
	pid_t				pid1;
	int					fd[2];
	int					dup_fd[2];
	int					last_fd;
	int					fd_in;
	int					fd_out;
	char				redir;
	char				*in_value;
	char				*out_value;
	char				*path;
	char				**cmdpath;
	struct s_branch		*cmd;
	struct s_shelgon	*pkcenter;
}			t_exegg;

typedef struct s_token
{
	struct	s_token *prev;
	struct	s_token *next;
	char            *value;
	int				type;
	int				error;
}   t_token;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	int				type;
	char			*value;	
}	t_ast;

typedef	struct s_shelgon
{
	struct s_token	*list_token;
	struct s_token	*current;
	struct s_ast	*top_root;
	struct s_ast	*tree;
	char			**envr;
	int		cmd_root;
}	t_shelgon;

void	execute_command(char *command, char **env);

/* LEXER FUNCTIONS */
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_new_token();
t_token	*token_type_exists(t_token *lst, int type);
int		is_token_type(t_token *token, int type);
t_token *tokenize(char *line);
void	free_tokens(t_token *head);

/* PARSER FUNCTIONS*/
t_ast	*parser(t_token *head, t_shelgon **shelgon);
t_ast 	*new_node_init();
t_ast	*new_pipe_node();
t_ast	*new_word_node(t_token *token);
t_ast	*new_redir_node(t_token *token);
t_ast	*new_env_node(t_token *token);
t_ast	*new_end_node();
void	free_ast(t_ast	*tree);

//command productions
t_ast	*create_command(t_token *head, t_shelgon **shelgon);
t_ast   *command_word(t_shelgon **shelgon);
t_ast   *command_prefix(t_shelgon **shelgon);
t_ast   *command_suffix(t_shelgon **shelgon);

//redirection productions
t_ast	*create_redirectout(t_shelgon **shelgon);
t_ast	*create_redirectin(t_shelgon **shelgon);

//executor functions
int		exeggutor(t_ast	*tree, t_shelgon *shelgon);
void	find_redir(t_ast *tree, t_exegg *exe, t_branch *cmds);
void	fst_child(t_ast *tree, t_exegg *exe, t_branch *cmds);
void	lst_child(t_ast *tree, t_exegg *exe, t_branch *cmds);
void	mid_child(t_ast *tree, t_exegg *exe, t_branch *cmds);
t_branch	*node_cmd(t_ast *tree);
void	get_cmd(t_ast *tree, t_branch **cmds);
void	ft_path(t_exegg *exe);
void	ft_error(int flg, t_exegg *exe);
int		ft_heredoc(t_ast *tree);
t_branch	*msh_lstlast(t_branch *lst);
void	my_close(int fd);

/*DEBUGGING*/
void	print_tree(t_ast *root);

t_ast	*connect_subtree(t_ast *root, t_ast *subtree, t_shelgon **shelgon, int dir);
