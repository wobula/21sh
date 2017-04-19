# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschramm <rschramm@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 14:23:11 by rschramm          #+#    #+#              #
#    Updated: 2017/03/21 10:39:38 by rschramm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = 21sh

CC = gcc

FLAG += -Wall -Werror -Wextra

SRC = ./srcs/main.c \
	  ./srcs/cd.c \
	  ./srcs/cd2.c \
	  ./srcs/env.c \
	  ./srcs/env_mod.c \
	  ./srcs/fork.c \
	  ./srcs/get_info.c \
	  ./srcs/path.c \
	  ./srcs/input_management.c \
	  ./srcs/redirect.c \
	  ./srcs/pipe_lst.c \
	  

OBJ = $(SRC:.c=.o)

LIBFT = libft/libftprintf.a \

all: $(NAME)

$(NAME): $(OBJ)
	@make re -C libft
	@gcc $(FLAG) -o $(NAME) $(SRC) $(LIBFT) -g
	@echo "\033[33;32mSystem Ready >:D"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "\033[33mCleaned..."

fclean:
	@make clean
	@make fclean -C libft
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[31mfCleaned..."

re: fclean all
