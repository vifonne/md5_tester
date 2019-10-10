# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifonne <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 19:05:19 by vifonne           #+#    #+#              #
#    Updated: 2019/01/06 12:33:18 by vifonne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		ft_memcpy.c			ft_bzero.c			ft_memset.c		\
					ft_memchr.c			ft_memccpy.c		ft_strncat.c	\
					ft_strcat.c			ft_strncpy.c		ft_strcpy.c		\
					ft_strdup.c			ft_strlen.c			ft_memcmp.c		\
					ft_strchr.c			ft_strrchr.c		ft_strstr.c		\
					ft_strcmp.c			ft_strncmp.c		ft_isalpha.c	\
					ft_isdigit.c		ft_isalnum.c		ft_isascii.c	\
					ft_isprint.c		ft_toupper.c		ft_tolower.c	\
					ft_strlcat.c		ft_memmove.c		ft_strnstr.c	\
					ft_memalloc.c		ft_memdel.c			ft_strnew.c		\
					ft_strdel.c			ft_strclr.c			ft_striter.c	\
					ft_striteri.c		ft_strmap.c			ft_strmapi.c	\
					ft_strequ.c			ft_strnequ.c		ft_strsub.c		\
					ft_strjoin.c		ft_strtrim.c		ft_putchar.c	\
					ft_putstr.c			ft_putendl.c		ft_putnbr.c		\
					ft_putchar_fd.c		ft_putstr_fd.c		ft_putendl_fd.c	\
					ft_putnbr_fd.c		ft_atoi.c			ft_strsplit.c	\
					ft_itoa.c			ft_strdjoin.c		ft_create_elem.c\
					ft_list_pushback.c	ft_list_pushfront.c get_next_line.c	\
					ft_print_tab_str.c	ft_print_tab_int.c	ft_max.c		\
					ft_sqrt.c			ft_split.c			ft_list_size.c	\
					ft_strjoind.c		ft_list_del.c		ft_strdjoind.c	\
					ft_print_list.c		ft_ltoi.c			ft_strisdigit.c
OBJ			=		$(SRCS:.c=.o)
CC			=		gcc -Wall -Wextra -Werror
NAME		=		libft.a

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CC) -I ./libft.h -c $(SRCS)
	@ar rcs $(NAME) $(OBJ)

%.o :	%.c ./libft.h
	@/bin/echo -n "="
	@$(CC) -I ./libft.h -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean $(NAME)
