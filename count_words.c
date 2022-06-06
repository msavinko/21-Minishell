#include "minishell.h"

int ft_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == '\'' || c == '\"' || c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

void words_in_quotes(int quotes_flag, int *i, int *words, char *str)
{
	if (str[++(*i)])
	{
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
		{
			(*i)++;
			return;
		}
		if (quotes_flag == SIN_Q)
		{
			while (str[(*i)] != '\'')
				(*i)++;
		}
		else if (quotes_flag == DOUB_Q)
		{
			while (str[(*i)] != '\"')
				(*i)++;
		}
	}
	(*words)++;
	(*i)++;
}

void count_nomal_symb(char *str, int *ind, int *num_words)
{
	int i;
	int words;

	i = *ind;
	words = *num_words;
	while (str[i] && !ft_separator(str[i]))
	{
		i++;
		if (str[i] == '\'')
		{
			words_in_quotes(1, &i, &words, str);
			words--;
		}
		else if (str[i] == '\"')
		{
			words_in_quotes(2, &i, &words, str);
			words--;
		}
	}
	*num_words = ++words;
	*ind = ++i;
}

void count_redirects(char *str, int *ind, int *num_words)
{
	int i;
	int words;

	i = *ind;
	words = *num_words;
	if (str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<')
			i++;
		words++;
		i++;
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			i++;
		words++;
		i++;
	}
	*num_words = words;
	*ind = i;
}

int count_words(char *str, int i, int words)
{
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '\'')
			words_in_quotes(SIN_Q, &i, &words, str);
		else if (str[i] == '\"')
			words_in_quotes(DOUB_Q, &i, &words, str);
		else if (str[i] == '|')
		{
			words++;
			i++;
		}
		else if (str[i] == '<' || str[i] == '>')
			count_redirects(str, &i, &words);
		else if (str[i] && !ft_separator(str[i]))
			count_nomal_symb(str, &i, &words);
		else
			i++;
	}
	return (words);
}
