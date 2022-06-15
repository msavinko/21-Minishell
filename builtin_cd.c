/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cut_tail_string(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	return (ft_substr(str, 0, i + 1));
}

static int	home_directory(t_com *com, char *home)
{
	char	*tmp;

	if (!com->arg || !ft_strcmp(com->arg[0], "~"))
	{
		if (chdir(home) == -1)
			return (1);
	}
	else
	{
		if (!ft_strncmp(com->arg[0], "~/", 2))
		{
			tmp = com->arg[0] + 1;
			com->arg[0] = ft_strjoin(home, "/");
			com->arg[0] = ft_strjoin(com->arg[0], tmp);
		}
		else
		{
			tmp = cut_tail_string(home);
			com->arg[0] = ft_strjoin(tmp, com->arg[0] + 1);
		}
		if (chdir(com->arg[0]) == -1)
			return (1);
	}
	return (0);
}

static int	change_directory(t_com *com, char *home, char *pwd, char *old_pwd)
{
	if (!com->arg || !ft_strncmp(com->arg[0], "~", 1))
	{
		if (home_directory(com, home))
			return (1);
	}
	else if (!ft_strcmp(com->arg[0], "."))
	{
		if (chdir(pwd) == -1)
			return (1);
	}
	else if (!ft_strcmp(com->arg[0], "-"))
	{
		if (chdir(old_pwd) == -1)
			return (1);
		ft_putendl_fd(old_pwd, 1);
	}
	else if (!ft_strcmp(com->arg[0], ".."))
	{
		if (chdir(cut_tail_string(pwd)) == -1)
			return (1);
	}
	else
		if (chdir(com->arg[0]) == -1)
			return (1);
	return (0);
}

// int	builtin_cd(t_com *com, t_envp *envp_list)
// {
// 	char	*home;
// 	char	*pwd;
// 	char	*old_pwd;

// 	if (!envp_list || !com)
// 		return (1);
// 	home = get_value_from_envp(envp_list, "HOME");
// 	pwd = get_value_from_envp(envp_list, "PWD");
// 	old_pwd = get_value_from_envp(envp_list, "OLDPWD");
// 	if (!home || !pwd || !old_pwd)
// 		return (1);
// 	if (change_directory(com, home, pwd, old_pwd))
// 	{
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		perror(com->arg[0]);
// 		return (1);
// 	}
// 	if (put_value_to_envp(envp_list, "OLDPWD", pwd))
// 		return (1);
// 	if (put_value_to_envp(envp_list, "PWD", getcwd(NULL, 0)))
// 		return (1);
// 	free(old_pwd);
// 	free(pwd);
// 	free(home);
// 	return (0);
// }

int	builtin_cd(t_com *com, t_envp *envp_list)
{
	char	*home;
	char	*pwd;
	char	*old_pwd;

	if (!envp_list || !com)
		return (1);
	home = get_value_from_envp(envp_list, "HOME");
	pwd = get_value_from_envp(envp_list, "PWD");
	old_pwd = get_value_from_envp(envp_list, "OLDPWD");
	if (change_directory(com, home, pwd, old_pwd))
	{
		ft_putstr_fd("Myshell 🐚: cd: ", 2);
		perror(com->arg[0]);
		return (1);
	}
	if (put_value_to_envp(envp_list, "OLDPWD", pwd))
		return (1);
	if (put_value_to_envp(envp_list, "PWD", getcwd(NULL, 0)))
		return (1);
	return (0);
}
