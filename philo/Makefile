# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:05:17 by mzhitnik          #+#    #+#              #
#    Updated: 2025/02/23 12:37:18 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
# NAME_B		:= so_long_bonus

CC = cc
CFLAGS		:= #-Wextra -Wall -Werror

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
# 		$(SRCS_B_PATH)/map_val_bonus.c \
# 		$(SRCS_B_PATH)/map_check_bonus.c \
# 		$(SRCS_B_PATH)/map_flood_check_bonus.c \
# 		$(SRCS_B_PATH)/error_bonus.c \
# 		$(SRCS_B_PATH)/animate_bonus.c \
# 		$(SRCS_B_PATH)/mlx_init_bonus.c \
# 		$(SRCS_B_PATH)/events_bonus.c \
# 		$(SRCS_B_PATH)/enemy_bonus.c \
# 		$(SRCS_B_PATH)/draw_instances_bonus.c

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

# $(NAME_B): $(LIBMLX) $(LIBS) $(OBJS_B) $(LIBFT)
# 	@$(CC) $(OBJS_B) $(LIBS) $(LIBS_FLAGS) $(LIBFT) $(HEADERS) -o $(NAME_B)
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
# 	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
# 	@echo "bonus and libft cleaning completed ..."

# fcleanb: cleanb
# 	@rm -f $(NAME_B)
# 	@echo "bonus force cleaning completed..."

# reb: fcleanb bonus

.PHONY: all clean fclean re bonus cleanb fcleanb reb
