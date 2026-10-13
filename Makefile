# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/06 18:21:55 by aiwane            #+#    #+#              #
#    Updated: 2026/08/18 12:18:37 by aiwane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= push_swap
BONUS_NAME	:= checker

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
INCLUDES	:= -Iinclude

SRC_DIR		:= src
BONUS_DIR	:= bonus
OBJ_DIR		:= obj

SRC_FILES	:= \
	core/main.c \
	core/parse.c \
	core/parse_tokens.c \
	core/init.c \
	stack/stack.c \
	stack/ops.c \
	stack/optimize.c \
	sort/sort_simple.c \
	sort/sort_medium.c \
	sort/sort_medium_utils.c \
	sort/sort_complex.c \
	sort/ranks.c \
	utils/output.c \
	utils/bench.c \
	utils/utils.c

OBJS		:= $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

SHARED_FILES	:= \
	core/parse_tokens.c \
	core/init.c \
	stack/stack.c \
	stack/ops.c \
	utils/utils.c

SHARED_OBJS		:= $(SHARED_FILES:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS		:= $(OBJ_DIR)/checker_bonus.o $(SHARED_OBJS)

HEADER		:= include/push_swap.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/checker_bonus.o: $(BONUS_DIR)/checker_bonus.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
