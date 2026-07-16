# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/17 14:20:05 by jfox              #+#    #+#              #
#    Updated: 2026/07/16 13:51:28 by jfox             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJECT_DIR ?= ./object_files
SRC_DIR = ./src
INC_DIR = ./include

SRC =	main.c \
		tokenize/tokenizing.c \
		execution/execution.c \
		environment/environment.c environment/environment_utils.c \
		parsing/parsing.c parsing/parsing_redirects.c \
		shell/shell.c shell/free.c

NAME = minishell
OBJ = $(SRC:%.c=$(OBJECT_DIR)/%.o)

CC = cc
CFLAGS += -Wall -Wextra -Werror -g -I$(INC_DIR) -MMD -MP

TOOLS = libft.a

USRPATH = $(shell pwd)

all: $(NAME) ping_make

# ---------- Build objects ----------
$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(CFLAGS)

# --------- Build minishell ----------
$(NAME): $(TOOLS) $(OBJ)
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJ) $(TOOLS) -lSDL2
	@echo "\033[32m--------The minishell executable and object files have been made--------\033[0m"

# -------- Utility libraries --------
$(TOOLS):
	@$(MAKE) -C libft

clean:
	@rm -rf $(OBJECT_DIR)
	@echo "\033[33m-----The minishell and libft Object_Files were removed successfully-----\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33m--------------The executable has been removed successfully--------------\033[0m"
	@$(MAKE) fclean -C libft
	@echo "\033[33m"
	@echo "=============================CLEAN COMPLETE============================="
	@echo "\033[0m"

re: ping_re fclean all

ping_make:
	@echo "\033[32m"
	@echo "=============================MAKE COMPLETE=============================="
	@echo "\033[0m"

ping_re:
	@echo "\033[31m"
	@echo "=======================REBUILDING THE EXECUTABLE========================"
	@echo "\033[0m"

valgrind: $(NAME)
	@echo clear && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=$(USRPATH)/readline.supp ./minishell

.PHONY: all clean fclean re tools ping_make ping_re valgrind

-include $(OBJ:.o=.d)
