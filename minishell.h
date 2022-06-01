/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:10:55 by marlean           #+#    #+#             */
/*   Updated: 2022/06/01 19:24:02 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct	s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

t_envp	*envp_new(char *content);
void	read_envp(char **env, t_envp *envp_list);
void	envp_add_front(t_envp **lst, t_envp *new);

#endif