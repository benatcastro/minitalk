 # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bena <bena@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 09:47:22 by becastro          #+#    #+#              #
#    Updated: 2022/05/07 16:40:49y bena             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
cc = gcc
AR = ar rc
RM	= rm -r
LIBFT = libft
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address -g3
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
HEADER  = ../includes/
SRC_DIR = srcs/ft_
OBJ_DIR = obj/

#files
SRC_FILES = printf printf_utils printf_utils2 is_arg print_args getflags print_precision print_prefix print_types print_types2 first_arg

SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

#rules

all: $(NAME)

$(NAME):$(OBJ)
	@make bonus -C libft
	@cp libft/libft.a .
	@mv libft.a $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@echo "Libraries compiled"

OBJF = .cache_exists

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
bonus : re
	@echo "bonus compiled"

out: re
	@$(CC) main.c libftprintf.a
	@./a.out

sanitize: re
	@$(CC) $(SANITIZE) main.c libftprintf.a
	@./a.out

valgrind: re
	@$(CC) main.c libftprintf.a
	@$(VALGRIND) ./a.out

clean:
	@$(RM) -rf $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	@$(RM) -f $(NAME)
	@$(RM) -f $(LIBFT)/libft.a

re: fclean all
