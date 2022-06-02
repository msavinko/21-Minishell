/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:10:55 by marlean           #+#    #+#             */
/*   Updated: 2022/06/02 16:39:26 by marlean          ###   ########.fr       */
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
	char				*flag;
	char				*arg;
	char				*delim;
	struct s_command	*next;
}	t_com;

//list_utils.c
t_envp	*envp_new(char *content);
void	read_envp(char **env, t_envp **envp_list);
void	envp_add_front(t_envp **lst, t_envp *new);

//signal_handler.c
int	signal_handler();
void	ctrl_c_handler(int sig);
#endif