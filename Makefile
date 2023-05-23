# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimarque <rimarque>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 12:57:07 by rimarque          #+#    #+#              #
#    Updated: 2023/05/23 12:20:18 by rimarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libftx/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

OBJ = src/pipex_aux.o \
		src/quotes.o

OBJ_MAND = src_mandatory/pipex.o \

OBJ_BONUS = src_bonus/main.o \
				src_bonus/pipex_bonus.o

all: $(NAME)

$(LIBFT):
	echo "compiling..."
	$(MAKE) --no-print-directory -C ./libftx
	echo "LIBFT created"

$(NAME): $(OBJ_MAND) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_MAND) $(OBJ) $(LIBFT) -o $(NAME)
	echo "Program READY"

bonus: $(OBJ_BONUS) $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ_BONUS) $(OBJ) $(LIBFT) -o bonus
		echo "Bonus READY"

clean:
	$(MAKE) --no-print-directory -C ./libftx
	rm -rf $(OBJ)
	rm -rf $(OBJ_MAND)
	rm -rf $(OBJ_BONUS)
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
