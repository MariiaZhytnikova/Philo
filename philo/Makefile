# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:05:17 by mzhitnik          #+#    #+#              #
#    Updated: 2025/03/05 11:10:55 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CC = cc
CFLAGS		:= -pthread -Wextra -Wall -Werror

HEADERS		:= -I ./inc

SRCS_PATH	:= ./src
OBJS_PATH	:= ./obj

SRCS := $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/utils.c \
		$(SRCS_PATH)/parse_args.c \
		$(SRCS_PATH)/init.c \
		$(SRCS_PATH)/simulation.c \
		$(SRCS_PATH)/sim_utils.c \
		$(SRCS_PATH)/routine.c

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
