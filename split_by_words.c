#include "minishell.h"

char	*write_redir(char *str, int *ind)
{
	char	*res;
	int		i;

	i = 0;
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
			i++;
	}
	res = ft_substr(str, 0, i);
	*ind += i;
	return (res);
}

int	count_space(char *str)
{
	int	i;
	int	count_one;
	int	count_double;

	i = 0;
	count_one = 0;
	count_double = 0;
	while (i < (int)ft_strlen(str))
	{
		if (ft_separator(str[i]) && count_one % 2 == 0 && count_double % 2 == 0)
			return (i);
		if (str[i] == '\'' && count_double % 2 == 0)
			count_one++;
		if (str[i] == '\"' && count_one % 2 == 0)
			count_double++;
		i++;
	}
	return (i);
}

char	*write_words(char *str, int *ind)
{
	t_words	*write_w;

	write_w = init_write_w(str);
	while (write_w->i < write_w->len)
	{
		if (str[write_w->i] == '\'' && write_w->count_double % 2 == 0)
		{
			write_w->count_one++;
			write_w->i++;
		}
		if (str[write_w->i] == '\"' && write_w->count_one % 2 == 0)
			write_w->count_double++;
		else
			write_w->res[write_w->j++] = str[write_w->i];
		write_w->i++;
	}
	write_w->res[write_w->j] = '\0';
	*ind += write_w->i;
	return (write_w->res);
}

char	**split_by_words(char *str)
{
	t_split	*split_w;
	int		i;
	int		j;

	split_w = init_split(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
			split_w->split_by_words[j++] = ft_substr(&str[i++], 0, 1);
		else if (str[i] == '<' || str[i] == '>')
			split_w->split_by_words[j++] = write_redir(&str[i], &i);
		else if (str[i + 1] && (!ft_strncmp(&str[i], "\'\'", 2)
				|| !ft_strncmp(&str[i], "\"\"", 2)))
			i += 2;
		else
			split_w->split_by_words[j++] = write_words(&str[i], &i);
	}
	split_w->split_by_words[j] = NULL;
	return (split_w->split_by_words);
}
