#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_envp *envp_list;
	t_com *com;
	char *read_str;
	char **split_words;

	envp_list = NULL;
	split_words = NULL;
	com = NULL;

	read_envp(env, &envp_list); // в envp_list записаны переменные окружения в односвязном списке
	//  read_commands(&com);		//ЗАГЛУШКА создан односвязный список из 3 листов (3 команды), изменять вручную
	signal_handler(); //обработка сигналов
	while (1)
	{
		read_str = read_the_line();
		if (ft_strlen(read_str) > 0)
		{
			add_history(read_str);
			if (!check_syntax(read_str))
			{
				replace_dollar(&read_str, envp_list);
				split_words = split_by_words(read_str); //Разбиваем строку на отдельные слова и спец символы
			}
			//    if (check_double_delim(split_words))
			//	error_double_delim(read_str);
			// print_array(split_words);
			//    make_struct(split_words, &com); // логические разледители.

			ft_clear_arr(split_words);
			// free(split_words);
			free(read_str);
		}
	}
	rl_clear_history();
	return (0);
}

void print_array(char **arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		printf("string %d: %s\n", i, arr[i]);
		i++;
	}
}
