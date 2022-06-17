/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:18:58 by rdanyell          #+#    #+#             */
/*   Updated: 2022/06/16 13:42:00 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_out_close(int save_stdout)
{
	close(0);
	dup2(save_stdout, 0);
	close(save_stdout);
}

void	pipe_close(t_com *com, int fd0, int fd1)
{
	if (com->next)
	{
		dup2(fd0, 0);
		close(fd0);
		close(fd1);
	}
}

void	free_pipe_struct(t_exec *exec)
{
	if (exec->path_cmd)
		free_array(exec->path_cmd);
	if (exec->cmd_full)
		free_array(exec->cmd_full);
	if (exec->env)
		free_array(exec->env);
}
