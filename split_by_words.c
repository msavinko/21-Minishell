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
	int		i;

	i = count_space(str);
	i++;
	res = ft_substr(str, 0, i);



	*ind += i;
	return (res);
}

char **split_by_words(char *str)
{
	char **split_by_words;
	int i;
	int words;
	int j;

	i = 0;
	j = 0;
	words = count_words(str, i, 0);
	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_by_words)
		exit(1);
	while(str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
			split_by_words[j++] = ft_substr(&str[i++], 0, 1);
		else if (str[i] == '<' || str[i] == '>')
			split_by_words[j++] = write_redir(&str[i], &i);
		else if (str[i + 1] && (!ft_strncmp(&str[i], "\'\'", 2) || !ft_strncmp(&str[i], "\"\"", 2)))
			i += 2;
		else
			split_by_words[j++] = write_words(&str[i], &i);
	}
	split_by_words[j] = NULL;
	return (split_by_words);
}



// char	*ft_strdup_n(const char *str, int num)
// {
// 	char	*res;
// 	int		i;

// 	printf("1 str: %s\n", str);
// 	i = 0;
// 	res = malloc(sizeof(char) * (num + 1));
// 	if (!(res))
// 		return (NULL);
// 	while (str[i] != '\0' && i < num)
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	printf("2 str: %s\n", str);
// 	return (res);
// }

// char	*write_redir(char *str, int *ind)
// {
// 	char	*res;
// 	int		i;

// 	i = 0;
// 	if (str[i] == '>')
// 	{
// 		i++;
// 		if (str[i] == '>')
// 			i++;
// 	}
// 	else if (str[i] == '<')
// 	{
// 		i++;
// 		if (str[i] == '<')
// 			i++;
// 	}
// 	res = ft_substr(str, 0, i);
// 	*ind += i;
// 	return (res);
// }

// int	count_space(char *str)
// {
// 	int	i;
// 	int	count_one;
// 	int	count_double;

// 	i = 0;
// 	count_one = 0;
// 	count_double = 0;
// 	while (i < (int)ft_strlen(str))
// 	{
// 		if (ft_separator(str[i]) && count_one % 2 == 0 && count_double % 2 == 0)
// 			return (i);
// 		if (str[i] == '\'' && count_double % 2 == 0)
// 			count_one++;
// 		if (str[i] == '\"' && count_one % 2 == 0)
// 			count_double++;
// 		i++;
// 	}
	
// 	return (i);
// }

// char	*write_words(char *str, int *ind)
// {
// 	// printf("3 my string: %s\n", str);
// 	char	*res;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = str;
// 	i = count_space(str);
// 	res = ft_substr(tmp, 0, i);
// 	// printf("4 my string: %s\n", str);

// 	// printf("len: %d res: %s and str: %s\n", i, res, str);

// 	*ind += i;
// 	// printf("ind: %d\n", *ind);
// 	return (res);
// }

// char **split_by_words(char *str)
// {
// 	char **split_by_words;
// 	int i;
// 	int words;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	words = count_words(str, i, 0);
// 	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
// 	if (!split_by_words)
// 		exit(1);

// 	while(str[i])
// 	{
// 		while (str[i] && ft_isspace(str[i]))
// 			i++;
// 		if (str[i] == '|')
// 		{
			
// 		printf("1 my string: %s\n", str);
// 			split_by_words[j++] = ft_substr(str, i++, 1);
// 		printf("2 my string: %s\n", str);

// 		}
// 		else if (str[i] == '<' || str[i] == '>')
// 			split_by_words[j++] = write_redir(&str[i], &i);
// 		else if (str[i + 1] && (!ft_strncmp(&str[i], "\'\'", 2) || !ft_strncmp(&str[i], "\"\"", 2)))
// 			i += 2;
// 		else
// 		{
// 			i++;
// 			// split_by_words[j++] = write_words(&str[i], &i);
// 		}
// 		printf("2 my string: %s, str[%d] = |%c|\n", str, i, str[i]);
// 	//	printf("i = %d pointer to %c\n", i, str[i]);
// 	}
// 	split_by_words[j] = NULL;
// 	return (split_by_words);
// }

