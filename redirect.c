/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:51:39 by rdanyell          #+#    #+#             */
/*   Updated: 2022/06/13 14:14:46 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_handler(t_com *com)
{
	int	output;
	int dup;

	//printf("Redirect\n");
	output = 0;
	if (com->delim == 2)
	{
		output = open(com->file, O_RDONLY);
		//printf("output infile: %d\n", output);
		if (output == -1)
		{
			ft_putstr_fd("Myshell 🐚: ", 2);
			ft_putstr_fd(com->file, 2);
			ft_putendl_fd(": No such file or directory", 2);
			// printf("%s: No such file or directory\n", com->file);
			g_exit_status = 126;
			return ;
		}
		dup2(output, 0);
		close(output);
	}
	if (com->delim == 3)
	{
		while (com->delim == 3 && com->file)
		{
			output = open(com->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			printf("output: %d\n", output);
			if (output == -1)
			{
				ft_putstr_fd("Myshell 🐚: ", 2);
				ft_putstr_fd(com->file, 2);
				ft_putendl_fd(": Permission denied", 2);
				// printf("%s: Permission denied\n", com->file);
				g_exit_status = 126;
				return ;
			}
			if (com->next)
				com = com->next;
			else
				break ;
		}
		printf("output: %d\n", output);
		dup = dup2(output, 1);
		close(output);
	}
	if (com->delim == 5)
	{
		while (com->delim == 5 && com->file)
		{
			output = open(com->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			// printf("output: %d\n", output);
			if (output == -1)
			{
				ft_putstr_fd("Myshell 🐚: ", 2);
				ft_putstr_fd(com->file, 2);
				ft_putendl_fd(": Permission denied", 2);
				// printf("%s: Permission denied\n", com->file);
				g_exit_status = 126;
				return ;
			}
			if (com->next)
				com = com->next;
			else
				break ;
		}
		// printf("output: %d\n", output);
		dup = dup2(output, 1);
		close(output);
	}
	if (com->delim == 4)
	{
		output = heredoc(com);
		dup2(output, 0);
		close(output);
	}
}
