#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "../libft/libft.h"

#define COMMAND 1
#define OPERATOR 2
#define S_STR 3
#define D_STR 4
#define S_CHAR 5
#define ENV 6

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*vr;
}	t_env;

typedef struct t_token
{
	struct	t_token *prev;
	struct	t_token *next;
	char            *value;
	int				type;
}   t_token;

void	execute_command(char *command, char **env);
t_token *lexer(char *line);

/* LEXER FUNCTIONS */
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);

/* ENV FUNCTIONS */
void	ms_addnode(t_env **h, char *s);
t_env	*ms_lstadd(char *s);
void	print_list(t_env *arr);