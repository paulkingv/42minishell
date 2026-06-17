# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/30 17:04:58 by jfox              #+#    #+#              #
#    Updated: 2026/06/17 14:47:02 by jfox             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJECT_DIR ?= ../object_files
SRC_DIR = ./src
INC_DIR = ../header

SRCC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
       ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
       ft_memcmp.c ft_memcpy.c ft_memset.c ft_memmove.c ft_putchar_fd.c \
       ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_split.c ft_strchr.c \
       ft_strtrim.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
       ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
       ft_strrchr.c ft_substr.c ft_toupper.c ft_tolower.c get_next_line.c \
       ft_printf.c ft_printf_putchar_fd.c ft_printf_putnbr_fd.c \
       ft_printf_pvoid.c ft_printf_putnbr_unsigned_fd.c \
       ft_printf_putnbr_hex_fd.c ft_printf_putstr_fd.c

OFILES = $(SRCC:%.c=$(OBJECT_DIR)/%.o)
CC = cc
CFLAGS += -Wall -Wextra -Werror -g -I$(INC_DIR) -MMD -MP
NAME = libft.a

all: $(NAME)

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJECT_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OFILES)
	@ar rcs ../$(NAME) $(OFILES)
	@echo "\033[32m-The libft Object_Files have been made. The libft Library has been made-\033[0m"

fclean:
	@rm -f ../$(NAME)
	@echo "\033[33m---------------The libft Library was removed successfully---------------\033[0m"

.PHONY: all fclean

-include $(OFILES:.o=.d)
