#include "minishell.h"

int ft_isdelim(char *s)
{
	if (!ft_strncmp(s, "|", 1) || !ft_strncmp(s, "<", 1) ||
		!ft_strncmp(s, ">", 1) || !ft_strncmp(s, "<<", 2) ||
		!ft_strncmp(s, ">>", 2))
		return (1);
	else
		return (0);
}

int delimetr(char *s)
{
	if (s[0] == '|')
		return (1);
	if (s[0] == '<' && s[1] == '\0')
		return (2);
	if (s[0] == '>' && s[1] == '\0')
		return (3);
	if (s[0] == '<' && s[1] == '<')
		return (4);
	if (s[0] == '>' && s[1] == '>')
		return (5);
	return (0);
}

void dollar_redirect(char *str, int *num)
{
	int i;

	i = *num + 2;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '$')
	{
		i++;
		while (str[i] && ft_isalnum(str[i + 2]))
			i++;
	}
	*num = i;
}