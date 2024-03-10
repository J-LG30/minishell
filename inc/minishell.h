#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
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


typedef struct t_token
{
	struct	t_token *prev;
	struct	t_token *next;
	char            *value;
	int				type;
	int				error;
}   t_token;

typedef struct t_ast
{
	struct t_ast	*left;
	struct t_ast	*right;
	int				type;
	char			*value;	
	int				in_fd;
	int				out_fd;
}	t_ast;

void	execute_command(char *command, char **env);

/* LEXER FUNCTIONS */
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_new_token();
t_token *tokenize(char *line);

/* PARSER FUNCTIONS*/
t_ast	*parser(t_token **head);
t_ast *new_node_init();
t_ast	*new_pipe_node();
t_ast	*new_word_node(t_token *token);
t_ast	*new_redir_node(t_token *token);
t_ast	*new_env_node(t_token *token);
t_ast	*new_end_node();