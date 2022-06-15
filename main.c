#include "minishell.h"

static void	check_args(int argc, char **argv)
{
	// Если будет свободное время, можно реализовать в этой функции исполнение файлов
	// Настоящая оболочка пробует открыть файл, название которого подано как аргумент
	// Ожидается, что это будет bash script
	// То есть содержимое файла исполняется строчка за строчкой сверху вниз
	// В качестве примера - скрипт для освобождения кэш-памяти: bash ./clean.sh
	// А пока такая вот заглушка:
	if (argc > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit (1);
	}
}

int main(int argc, char **argv, char **env)
{
	t_envp *envp_list;
	t_com *com;
	char *read_str;
	char **split_words;

	check_args(argc, argv);
	envp_list = NULL;
	split_words = NULL;
	com = NULL;
	read_envp(env, &envp_list); // в envp_list записаны переменные окружения в односвязном списке
	signal_handler(); //обработка сигналов
	while (1)
	{
		signal_handler(); //обработка сигналов
		read_str = read_the_line();
		if (ft_strlen(read_str) > 0)
		{
			add_history(read_str);
			if (!check_syntax(read_str))
			{
				replace_dollar(&read_str, envp_list);
				split_words = split_by_words(read_str); //Разбиваем строку на отдельные слова и спец символы
				if (split_words != NULL && split_words[0] != NULL)
				{
					if (check_double_delim(split_words))
						printf("syntax error near unexpected token `newline'\n");
					print_array(split_words);
					make_struct(split_words, &com); // логические разледители.
					if (com)
						execute(com, &envp_list);
				}
			}
			
			// free_com_list(com);
			free_array(split_words);
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


//hey >> lol  - SEGA
//hey
// "/bin/ls"
// cat lol.c
// cat lol.c > 1
// cat lol.c >> 1
// cat lol.c > 1 | wc
// cat < lol.c
// cat < lol.c | ls
// cat < lol.c | cat
// ls -a | wc -l
// ls | wc -l
// cat lol.c > 1 2 3 > 4

// export PATH=/Users/marlean/.brew/bin:/Users/marlean/CMake.app/Contents/bin:/Users/marlean/CMake.app/Contents/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/bin/ls