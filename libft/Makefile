# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cosi <cosi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 17:44:21 by edeveze           #+#    #+#              #
#    Updated: 2017/07/02 02:21:44 by cosi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable

NAME = libft.a

# Includes

INC = includes

# Files

SRC =		ft_atoi.c \
			ft_atoi_base.c \
			ft_bzero.c \
			ft_countdigits.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_iswhitespaces.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_lstadd.c \
			ft_lstaddlast.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strndup.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoinfree.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_swap.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c\
			palloc.c\

OBJ = $(SRC:.c=.o)

# Compilation

CC = gcc

CFLAGS += -Wall -Wextra -Werror

# Rules

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^ -I$(INC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
