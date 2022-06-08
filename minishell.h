
#ifndef MINISHELL_H
#define MINISHELL_H
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>

#define WHITE_SPACES " \t\v\r\f"
// delimeters
#define PIPE 1
#define LEF_SIN_REDIR 2
#define RIGH_SIN_REDIR 3
#define LEF_DOUB_REDIR 4
#define RIGH_DOUB_REDIT 5
#define SIN_Q 1
#define DOUB_Q 2

int g_exit_code;

typedef struct s_envp
{
	char *key;
	char *value;
	struct s_envp *next;
} t_envp;

typedef struct s_command
{
	char *name;
	char **arg;
	int delim;
	char *file;
	struct s_command *next;
} t_com;

// list_utils.c
char	*read_the_line(void);
void	read_envp(char **env, t_envp **envp_list);
t_envp	*envp_new(char *content);
void	envp_add_front(t_envp **lst, t_envp *new);

// signal_handler.c
void ctrl_c_handler(int signum);
int signal_handler();

// utils_draft
void read_commands(t_com **com);
t_com *com_new(char *name, char **arg, int delim);
void com_add_back(t_com **lst, t_com *new);

// count_words.c
int		ft_separator(char c);
void	count_redirects(char *str, int *ind, int *num_words);
void	count_rest(char *str, int *ind, int *num_words);
int		count_words(char *str, int i, int words);

// split_by_words.c
char	*write_redir(char *str, int *ind);
int		count_space(char *str);
char	*write_words(char *str, int *ind);
char	**write_split_words(char **split_by_words, char *str);
char	**split_by_words(char *str);

void print_array(char **arr);


//******************************************************************************


// check_sytax.c
int		ft_check_eve_quotes(char *str);
int		ft_check_first_end(char *str);
void	check_syntax(char *str);
int		check_double_delim(char **arr);

// replace_dollar.c
char	*subst_dollar(char *com, t_envp	*envp_list);
char	*change_dollar(char *str, int n, t_envp	*envp_list);
int		replace_dollar(char *str, t_envp *envp_list);

// make_struct.c
t_com	*com_new1(char *name, char **arg, int delim);
int		ft_isdelim(char *s);
int		delimetr(char *s);
void	ft_lstprint(t_com **com);
int		make_arg(char **arg, char **arr, int i);
t_com	*make_struct(char **arr);

#endif



//>1 echo 333 > 2 345 >3 567

// hey 'how are ' "" "you" ?
// hey 'how are' ""
// hey ''
// hey >><|'kk'


// echo 'str1'str2"str3 $PWD str4" "str5"'$PWD' $PWD "$PWD"

//hey | > kk 'dd'"asdf '' "a