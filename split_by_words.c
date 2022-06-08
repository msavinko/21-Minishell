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
	char	*res;
	int		len;
	int		i;
	int		j;
	int		count_one;
	int		count_double;

	count_one = 0;
	count_double = 0;
	j = 0;
	i = 0;
	len = count_space(str);
	res = malloc(sizeof(char *) * len + 1);
	if (!res)
		exit(1);
	while (i < len)
	{
		if (str[i] == '\'' && count_double % 2 == 0)
		{
			count_one++;
			i++;
		}
		if (str[i] == '\"' && count_one % 2 == 0)
		{
			count_double++;
			i++;
		}
		else
		{
			res[j] = str[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	*ind += i;
	return (res);
}

char	**split_by_words(char *str)
{
	char	**split_by_words;
	int		i;
	int		words;
	int		j;

	i = 0;
	j = 0;
	words = count_words(str, i, 0);
	printf("words: %d\n", words);
	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_by_words)
		exit(1);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
			split_by_words[j++] = ft_substr(&str[i++], 0, 1);
		else if (str[i] == '<' || str[i] == '>')
			split_by_words[j++] = write_redir(&str[i], &i);
		else if (str[i + 1] && (!ft_strncmp(&str[i], "\'\'", 2)
				|| !ft_strncmp(&str[i], "\"\"", 2)))
			i += 2;
		else
			split_by_words[j++] = write_words(&str[i], &i);
	}
	split_by_words[j] = NULL;
	return (split_by_words);
}
