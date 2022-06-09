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
	char *rez;
	char *head;
	char *com;
	char *tail;
	int i;
	t_envp *tmp;

	printf("we here\n");
	n = *num;
	rez = ft_substr(str, 0, ft_strlen(str));
	tmp = envp_list;
	head = ft_substr(rez, 0, n);
	printf("head: |%s|\n", head);
	i = n;
	printf("i symb: |%c|\n", str[i]);
	while (str[i] && ft_isalnum(str[i + 2]))
		i++;
	printf("UNTIL symb: |%c|\n", str[i]);

	com = ft_substr(str, n + 1, i - n + 1);
	printf("com: |%s|\n", com);
	tail = ft_substr(str, i + 2, 1000);

	com = subst_dollar(com, envp_list);
	rez = ft_strjoin(head, com);
	rez = ft_strjoin(rez, tail);
	printf("rez = %s\n", rez);
	envp_list = tmp;
	str = rez;
	*num = 0;
	return (rez);
}

int replace_dollar(char **str, t_envp *envp_list)
{
	int count_one;
	int count_double;
	int i;

	count_one = 0;
	count_double = 0;
	i = 0;

	while ((*str)[i])
	{
		if ((*str)[i] == '$' && count_one % 2 == 0)
		{
			*str = change_dollar(*str, &i, envp_list);
			count_one = 0;
			count_double = 0;
		}
		if ((*str)[i] == '\'' && count_double % 2 == 0)
			count_one++;
		if ((*str)[i] == '\"' && count_one % 2 == 0)
			count_double++;
		i++;
	}

	return (0);
}
