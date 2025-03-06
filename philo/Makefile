# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:05:17 by mzhitnik          #+#    #+#              #
#    Updated: 2025/02/24 11:56:14 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
# NAME_B		:= philo_bonus

CC = cc
CFLAGS		:= -pthread -Wextra -Wall -Werror

HEADERS		:= -I ./inc

SRCS_PATH	:= ./src
# SRCS_B_PATH := ./src_bonus
OBJS_PATH	:= ./obj
# OBJS_B_PATH	:= ./obj_bonus

SRCS := $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/utils.c \
		$(SRCS_PATH)/parce_args.c \
		$(SRCS_PATH)/init.c \
		$(SRCS_PATH)/simulation.c \
		$(SRCS_PATH)/routine.c

# SRCS_B := $(SRCS_B_PATH)/main_bonus.c \
# 		$(SRCS_B_PATH)/utils_bonus.c \
# 		$(SRCS_B_PATH)/parce_args_bonus.c \
# 		$(SRCS_B_PATH)/init_bonus.c \
# 		$(SRCS_B_PATH)/simulation_bonus.c \
# 		$(SRCS_B_PATH)/routine_bonus.c

OBJS	:= $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
# OBJS_B	:= $(SRCS_B:$(SRCS_B_PATH)/%.c=$(OBJS_B_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME) -fsanitize=address
	@echo "$(NAME) building completed ..."

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@


# bonus: $(NAME_B)

# $(NAME_B): $(OBJS_B)
# 	@$(CC) $(OBJS_B) $(HEADERS) -o $(NAME_B)
# 	@echo "$(NAME_B) building completed ..."

# $(OBJS_B_PATH):
# 	@mkdir -p $(OBJS_B_PATH)

# $(OBJS_B_PATH)/%.o: $(SRCS_B_PATH)/%.c | $(OBJS_B_PATH)
# 	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@echo "cleaning completed ..."

fclean: clean
	@rm -f $(NAME)
	@echo "force cleaning completed..."

re: fclean all

# cleanb:
# 	@rm -rf $(OBJS_B_PATH)
# 	@echo "bonus and libft cleaning completed ..."

# fcleanb: cleanb
# 	@rm -f $(NAME_B)
# 	@echo "bonus force cleaning completed..."

# reb: fcleanb bonus

.PHONY: all clean fclean re bonus cleanb fcleanb reb
