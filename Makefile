# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edeveze <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/21 15:08:58 by edeveze           #+#    #+#              #
#    Updated: 2017/09/28 20:29:42 by edeveze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME = lem-in

# Sources
SRC = 	main.c\
		parsing.c\
		room.c\
		tube.c\

# Includes
INC = -I includes -I libft/includes

# Objects
OBJ = $(SRC:.c=.o)

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror
PRGFLAGS = -L libft/ libft/libft.a

# Colors
CYAN = \033[1;36m
RED = \033[0;31m
NC = \033[0m

# Rules

all : lib $(NAME)

lib:
	@make -C libft

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(PRGFLAGS) -o $@ $(OBJ)
	@echo "$(CYAN)██╗     ███████╗███╗   ███╗    ██╗███╗   ██╗"
	@echo "██║     ██╔════╝████╗ ████║    ██║████╗  ██║"
	@echo "██║     █████╗  ██╔████╔██║    ██║██╔██╗ ██║"
	@echo "██║     ██╔══╝  ██║╚██╔╝██║    ██║██║╚██╗██║"
	@echo "███████╗███████╗██║ ╚═╝ ██║    ██║██║ ╚████║"
	@echo "╚══════╝╚══════╝╚═╝     ╚═╝    ╚═╝╚═╝  ╚═══╝$(NC)"
                                            
                                                            

%.o: %.c libft/libft.a
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	@rm -rf $(OBJ)
	@make -C libft clean

fclean : clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@echo "$(RED)---Lem_in removed completely---$(NC)"

re : fclean all

.PHONY: all clean fclean re
