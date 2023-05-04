# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 12:57:07 by rimarque          #+#    #+#              #
#    Updated: 2023/05/04 11:27:07 by rimarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libftx/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

#OBJ =

OBJ_MAND = src_mandatory/pipex.o

#OBJ_BONUS =

all: $(NAME)

$(LIBFT):
	echo "compiling..."
	$(MAKE) --no-print-directory -C ./libftx
	echo "LIBFT created"

$(NAME): $(OBJ_MAND) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_MAND) $(LIBFT) -o $(NAME)
	echo "Program READY"

#bonus: $(OBJ_BONUS) $(OBJ) $(LIBFT)
#		$(CC) $(CFLAGS) $(OBJ_BONUS) $(OBJ) $(LIBFT) -o checker
#		echo "Program checker READY"

clean:
	$(MAKE) --no-print-directory -C ./libftx
#	rm -rf $(OBJ)
	rm -rf $(OBJ_MAND)
#	rm -rf $(OBJ_BONUS)
	echo "Object files CLEAN"

fclean: clean
	$(MAKE) fclean --no-print-directory -C ./libftx
	rm -rf $(NAME)
	rm -rf checker
	echo "All files CLEAN"

re: fclean all

bre: fclean bonus

.SILENT:

.PHONY: all clean fclean re
