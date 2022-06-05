/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariasavinova <mariasavinova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:10:55 by marlean           #+#    #+#             */
/*   Updated: 2022/06/05 20:31:17 by mariasavino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# define WHITE_SPACES " \t\v\r\f"
//delimeters
# define PIPE 1
# define LEF_SIN_REDIR 2
# define RIGH_SIN_REDIR 3
# define LEF_DOUB_REDIR 4
# define RIGH_DOUB_REDIT 5
# define SIN_Q 1
# define DOUB_Q 2

int	g_exit_code;

typedef struct	s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct	s_command
{
	char				*name;
	char				**arg;
	int					delim;
	struct s_command	*next;
}	t_com;

//list_utils.c
char	*read_the_line(void);
t_envp	*envp_new(char *content);
void	read_envp(char **env, t_envp **envp_list);
void	envp_add_front(t_envp **lst, t_envp *new);

//signal_handler.c
int		signal_handler();
void	ctrl_c_handler(int signum);

//utils_draft
void	read_commands(t_com **com);
t_com	*com_new(char *name, char **arg, int delim);
void	com_add_back(t_com **lst, t_com *new);

//check_sytax.c
void	check_syntax(char **str);
int		ft_check_first_end(char **str);
int		ft_check_eve_quotes(char *str);


//split_by_words
char	*in_quotes(char *str, int quote_flag);
char	**split_by_words(char	*str);

//count_words.c
int		ft_separator(char c);
void	words_in_quotes(int	quotes_flag, int *i, int *words, char *str);
void	count_nomal_symb(char *str, int *ind, int *num_words);
void	count_redirects(char *str, int *ind, int *num_words);
int		count_words(char *str, int i, int words);

void	print_array(char **arr, int words);



int	replace_dollar(char *str, t_envp *envp_list);

#endif