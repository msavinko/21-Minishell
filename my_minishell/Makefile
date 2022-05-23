# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marlean <marlean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 15:12:33 by marlean           #+#    #+#              #
#    Updated: 2022/05/23 15:55:00 by marlean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_MS	=	minishell

LIB_DIR	=	libft/
LIBFT	=	libft/libft.a
RL_INCLUDE	=	$(HOME)/.brew/Cellar/readline/8.1/include
RL_LIB		=	$(HOME)/.brew/Cellar/readline/8.1/lib

HEADER_MS	=	minishell.h
FILES_MS	=	try.c \



OBJ_MS		=	$(FILES_MS:%.c=%.o)

FLAGS_MS	=	-Wall -Wextra -Werror

.PHONY	: all clean fclean re libft

all		: libft $(NAME_MS)

libft	:
			@make -C $(LIB_DIR)

#сборка исполняемого файла
$(NAME_MS):	$(OBJ_MS)
	cc $(FLAGS_MS) -L$(shell brew --prefix readline)/lib -lreadline $(OBJ_MS) $(LIBFT) -o $@ 

#компиляция объектных файлов
%.o	:	%.c $(LIBFT) $(HEADER_MS) Makefile
	cc $(FLAGS_MS) -c $< -o $@

clean	:
	rm -f $(OBJ_MS)
	make -C $(LIB_DIR) clean

fclean	:
	rm -f $(NAME_MS)
	MAKE -C $(LIB_DIR) fclean

re		: fclean all