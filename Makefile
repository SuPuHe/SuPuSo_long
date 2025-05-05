# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 10:19:05 by omizin            #+#    #+#              #
#    Updated: 2025/05/05 11:06:34 by omizin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET_COLOR	= \033[0m			# Reset to default color
YELLOW		= \033[1;33m		# Brighter yellow
BLUE		= \033[1;34m		# Bright blue
GREEN		= \033[1;32m		# Bright green
RED			= \033[1;31m		# Bright red
CYAN		= \033[1;36m		# Bright cyan

NAME = so_long

SUPULIB_DIR = SuPuLib
SUPULIB_REPO = https://github.com/SuPuHe/SuPuLib.git
SUPULIB_A = $(SUPULIB_DIR)/SuPuLib.a
INCS_DIR = includes
OBJS_DIR = objs
SRCS_DIR = srcs

INCLUDE = -I$(INCS_DIR) -I$(SUPULIB_DIR)/libft/includes -I$(SUPULIB_DIR)/ft_printf/includes -I$(SUPULIB_DIR)/get_next_line/includes
CFLAGS = -Wall -Wextra -Werror $(INCLUDE)
CC = cc

RM = rm -rf

SRCS = so_long.c

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(SUPULIB_A) $(NAME)

$(SUPULIB_DIR):
	@git clone $(SUPULIB_REPO) $(SUPULIB_DIR)
	@echo "$(GREEN)SuPuLib cloned successfully$(RESET_COLOR)"

$(SUPULIB_A): | $(SUPULIB_DIR)
	@$(MAKE) -C $(SUPULIB_DIR)

$(NAME): $(OBJS) $(SUPULIB_A)
	@$(CC) $(CFLAGS) $(OBJS) $(SUPULIB_A) -o $(NAME)
	@echo "$(GREEN)so_long compiled successfully$(RESET_COLOR)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(SUPULIB_DIR) clean
	@echo "$(GREEN)Clean sucessfully$(RESET_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(SUPULIB_DIR) fclean
	@echo "$(GREEN)Fclean sucessfully$(RESET_COLOR)"

re: fclean all

.PHONY: all clean fclean re
