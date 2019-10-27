# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifonne <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 10:20:14 by vifonne           #+#    #+#              #
#    Updated: 2019/10/27 13:58:27 by vifonne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ssl

SRC_DIR		=	srcs
SRC			=	main.c				\
				md5.c				\
				md5_utils.c			\
				error.c				\
				sha256.c			\
				utils.c
OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)
INC_DIR		=	includes

CC			=	gcc -fsanitize=address -g
CFLAGS		=	-Wall -Wextra -Werror -I ./libft -I $(INC_DIR)

LIBFT		=	./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) -o $@ $^

$(LIBFT):
	$(MAKE) -C ./libft

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@/bin/mkdir $@
	@/bin/mkdir $@/op
	@/bin/mkdir $@/visual

clean:
	@echo "Cleaning $(NAME)"
	@$(MAKE) -C ./libft clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Full clean $(NAME)"
	@$(MAKE) -C ./libft fclean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
