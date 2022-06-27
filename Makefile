CC = gcc
NAME = minitol
MINILIB_FLAGS = -framework openGL -framework AppKit #-lmlx
CC_FLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address -g3
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
SRC_DIR = srcs/
OBJ_DIR = objs/
INCLUDES = includes/
LIBRARIES_DIR = libraries/

LIBRARIES_FILES = libft
SRC_FILES = client server

SRC			=	$(addprefix $(SRC_DIR)), $(addsuffix .c, $(SRC_FILES))

LIBRARIES	=	$(addprefix $(LIBRARIES_DIR), $(addsuffix .a, $(LIBRARIES_FILES)))

all : $(NAME)



$(NAME):
	@mkdir -p libraries
	@make -C libft

server: $(NAME)
	$(CC) $(CC_FLAGS) $(SRC_DIR)server.c $(LIBRARIES_DIR)libft.a -I $(INCLUDES) -o server.exec

client: $(NAME)
	$(CC) $(CC_FLAGS) $(SRC_DIR)client.c -I $(INCLUDES) $(LIBRARIES) -o client.exec

clean:

fclean:
	@rm -rf $(LIBRARIES_DIR)
