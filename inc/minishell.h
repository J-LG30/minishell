/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:43:28 by jle-goff          #+#    #+#             */
/*   Updated: 2024/04/29 18:06:11 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define XOPEN_SOURCE 700
# define WORD 1
# define S_STR 2
# define D_STR 3
# define S_CHAR 4
# define ENV 5
# define PIPE 6
# define REDIR_IN 7
# define REDIR_OUT 8
# define REDIR_APP 9
# define REDIR_DELIMIT 10
# define END 11

# define LEFT 20
# define RIGHT 21

# define IN_CHILD 14

# define ANGRY "(╯°□ °)╯︵ ┻━┻"

# define WRONG_CMD 2
# define BTIN 3
# define CTRL_D 1

volatile extern int		g_sig;

typedef struct s_env
{
	struct s_env		*prev;
	struct s_env		*next;
	char				*vr;
	char				*cpy;
	int					prnt;
}						t_env;

typedef struct s_branch
{
	struct s_branch		*prev;
	struct s_branch		*next;
	int					pipe[1];
	char				*cmd;
	char				**full_cmd;
	struct s_ast		*ref;
}						t_branch;

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
	struct s_env		*env;
	struct s_branch		*cmd;
	struct s_shelgon	*pkcenter;
}						t_exegg;

typedef struct s_token
{
	struct s_token		*prev;
	struct s_token		*next;
	char				*value;
	char				*copy;
	int					type;
	int					error;
}						t_token;

typedef struct s_ast
{
	struct s_ast		*left;
	struct s_ast		*right;
	int					type;
	char				*value;
}						t_ast;

typedef struct s_shelgon
{
	struct s_token		*list_token;
	struct s_token		*current;
	struct s_ast		*top_root;
	struct s_ast		*tree;
	struct s_exegg		*exe;
	char				**envr;
	int					cmd_root;
	int					status;
	struct s_env		*env;
}						t_shelgon;

void					execute_command(char *command, char **env);

/* LEXER FUNCTIONS */
t_token					*ft_tokenlast(t_token *lst);
void					ft_tokenadd_back(t_token **lst, t_token *new);
t_token					*ft_new_token(void);
t_token					*token_type_exists(t_token *lst, int type);
int						is_token_type(t_token *token, int type);
t_token					*tokenize(char *line, t_shelgon *shelgon);
void					free_tokens(t_token *head);
int						unclosed_quotes(t_token *token);
char					*rm_quotes(t_token *token);
void					expansion(t_token *token, t_shelgon *shelgon);
int						handle_word(t_token *token, t_shelgon *shelgon);

/* PARSER FUNCTIONS*/
t_ast					*parser(t_token *head, t_shelgon **shelgon);
t_ast					*new_node_init(void);
t_ast					*new_pipe_node(t_token *token);
t_ast					*new_word_node(t_token *token);
t_ast					*new_redir_node(t_token *token);
t_ast					*new_env_node(t_token *token);
t_ast					*new_end_node(void);
void					free_ast(t_ast *tree);

/*SIGNALS*/
void					sig_handler(int sig);
void					child_sig_handler(int sig);
void					set_prompt_handler(void);
void					set_child_handler(void);
void					set_heredoc_handler(void);
// command productions
t_ast					*create_command(t_token *head, t_shelgon **shelgon);
t_ast					*command_word(t_shelgon **shelgon);
t_ast					*command_prefix(t_shelgon **shelgon);
t_ast					*command_suffix(t_shelgon **shelgon);

// redirection productions
t_ast					*create_redirectout(t_shelgon **shelgon);
t_ast					*create_redirectin(t_shelgon **shelgon);

// executor functions
int						exeggutor(t_ast *tree, t_shelgon *shelgon, t_env *env);
void					find_redir(t_ast *tree, t_exegg *exe, t_branch *cmds);
void					which_child(t_ast *tree, t_exegg *exe, t_branch *cmds);
void					ft_pipe(t_ast *tree, t_exegg *exe, t_branch *cmds);
int						pipe_it(t_ast *tree, t_shelgon *shelgon, t_branch *cmds,
							t_exegg *exe);
void					fst_child(t_ast *tree, t_exegg *exe, t_branch *cmds);
void					lst_child(t_ast *tree, t_exegg *exe, t_branch *cmds);
void					mid_child(t_ast *tree, t_exegg *exe, t_branch *cmds);
int						get_cmd(t_ast *tree, t_branch **cmds, t_exegg *exe);
void					only_redir(t_ast *tree, t_exegg *exe);
char					*try_cmd(char *cargs, char **cpath);
void					ft_path(t_exegg *exe, t_env *env);
char					**ms_split(char const *s, char c);
void					ft_error(int flg, t_exegg *exe);
t_branch				*msh_lstlast(t_branch *lst);
int						ft_heredoc(t_ast *tree);
t_branch				*node_cmd(t_ast *tree);
char					*get_path(t_env	*env);

// Built in functions
int						is_btin(char *cmds);
void					run_btin(t_ast *tree, t_exegg *exe, t_branch *cmds,
							int flg);
t_env					*env(t_shelgon *shell, char **envp, int flg, int rexit);
void					print_list(t_env *arr);
void					ms_addnode(t_env **arr, char *s);
void					ms_addexp(t_env **arr, char *s);
t_env					*ms_lstadd(char *s);
void					export(t_branch *cmds, t_shelgon *shell, int flg);
void					echo(char **cmds, int flg, t_shelgon *shelgon);
void					pwd(int flg, t_shelgon *shelgon);
void					cd(char *arg, int flg, t_shelgon *shelgon);
void					ft_exit(t_shelgon *shelgon, t_branch *cmds,
							t_exegg *exe);
void					unset(t_shelgon *shell, char **cmds, int flg);
int						ft_strrem(char *str1, char *str2);

/*FREEING*/
void					free_shelgon(t_shelgon *sh);
void					free_exegg(t_exegg *exe);
void					free_env(t_env *env);
void					free_all(t_shelgon *shelgon, t_exegg *exe, int flag);
void					free_tokens(t_token *head);
void					free_ast(t_ast *tree);

/*DEBUGGING*/
void					print_tree(t_ast *root);
t_ast					*connect_subtree(t_ast *root, t_ast *subtree,
							t_shelgon **shelgon, int dir);
#endif