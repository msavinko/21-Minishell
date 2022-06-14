#include "minishell.h"

char *subst_dollar(char *com, t_envp *envp_list)
{
	while (envp_list)
	{
		if (!ft_strncmp(com, envp_list->key, 1000))
			return (envp_list->value);
		envp_list = envp_list->next;
	}
	return ("");
}

char *change_dollar(char *str, int *num, t_envp *envp_list)
{
	int n;
	int i;
	t_envp *tmp;
	t_dollar *doll;
	char *tmp_str;

	doll = malloc(sizeof(t_dollar));
	n = *num;
	doll->rez = ft_substr(str, 0, ft_strlen(str));

	tmp = envp_list;
	tmp_str = doll->rez;
	doll->head = ft_substr(doll->rez, 0, n);
	if (tmp_str)
		free(tmp_str);
	i = n;
	while (str[i] && ft_isalnum(str[i + 2]))
		i++;
	doll->com = ft_substr(str, n + 1, i - n + 1);
	doll->tail = ft_substr(str, i + 2, 1000);
	tmp_str = doll->com;
	doll->com = subst_dollar(doll->com, envp_list);
	if (tmp_str)
		free(tmp_str);
	doll->rez = ft_strjoin(doll->head, doll->com);
	tmp_str = doll->rez;
	doll->rez = ft_strjoin(doll->rez, doll->tail);
	if (tmp_str)
		free(tmp_str);
	envp_list = tmp;
	str = doll->rez;
	if (doll->head)
		free(doll->head);
	if (doll->tail)
		free(doll->tail);
	if (doll)
		free(doll);
	*num = 0;
	return (doll->rez);
}

int replace_dollar(char **str, t_envp *envp_list)
{
	int count_one;
	int count_double;
	int i;
	char *tmp;

	count_one = 0;
	count_double = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && count_one % 2 == 0)
		{
			if ((*str)[i + 1] && (*str)[i + 1] != '?')
			{
				tmp = *str;
				*str = change_dollar(*str, &i, envp_list);
				if (tmp)
					free(tmp);
				count_one = 0;
				count_double = 0;
			}
		}
		if ((*str)[i] == '\'' && count_double % 2 == 0)
			count_one++;
		if ((*str)[i] == '\"' && count_one % 2 == 0)
			count_double++;
		i++;
	}
	return (0);
}

// hey lala $PWD$SHELL
// hey $lala $1 $PWD kk''

// hey lala /Users/mariasavinova/Desktop / 21 - Minishell / bin / zsh
