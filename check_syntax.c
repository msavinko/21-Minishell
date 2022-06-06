#include "minishell.h"

int ft_check_eve_quotes(char *str)
{
	int count_one;
	int count_double;

	count_one = 0;
	count_double = 0;
	while (*str)
	{
		if (*str == '\'' && count_double % 2 == 0)
			count_one++;
		if (*str == '\"' && count_one % 2 == 0)
			count_double++;
		str++;
	}
	if (count_double % 2 == 0 && count_one % 2 == 0)
		return (0);
	else
		return (1);
}

int ft_check_first_end(char **str)
{
	char *tmp;
	char *trim_line;

	trim_line = ft_strtrim(*str, WHITE_SPACES);
	free(*str);
	*str = trim_line;
	tmp = trim_line;
	if (*tmp == '|' || *tmp == '<' || *tmp == '>')
		return (1);
	while (*tmp)
		tmp++;
	tmp--;
	if (*tmp == '|' || *tmp == '<' || *tmp == '>')
		return (1);
	free(trim_line);
	return (0);
}

void check_syntax(char **str)
{
	if (!ft_strlen(*str) || ft_check_eve_quotes(*str) || ft_check_first_end(str))
	{
		printf("syntax error near unexpected token `newline'");
		rl_clear_history();
		exit(1);
	}
	else
		return;
}
