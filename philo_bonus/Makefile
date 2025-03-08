# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:05:17 by mzhitnik          #+#    #+#              #
#    Updated: 2025/03/08 16:13:40 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo_bonus

CC = cc
CFLAGS		:= -pthread -Wextra -Wall -Werror

HEADERS		:= -I ./inc

SRCS_PATH	:= ./src
OBJS_PATH	:= ./obj

SRCS := $(SRCS_PATH)/main_bonus.c \
		$(SRCS_PATH)/utils_bonus.c \
		$(SRCS_PATH)/parce_args_bonus.c \
		$(SRCS_PATH)/sim_utils_bonus.c \
		$(SRCS_PATH)/simulation_bonus.c \
		$(SRCS_PATH)/routine_bonus.c

OBJS	:= $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME)
	@echo "$(NAME) building completed ..."

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@echo "cleaning completed ..."

fclean: clean
	@rm -f $(NAME)
	@echo "force cleaning completed..."

re: fclean all

.PHONY: all clean fclean re
