CC = gcc
NAME = minitol
MINILIB_FLAGS = -framework openGL -framework AppKit #-lmlx
CC_FLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address -g3
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
SRC_DIR = srcs/
OBJ_DIR = objs/
LIBRARIE = ft_printf/libftprintf.a

INCLUDE = ft_printf/includes/

SRC_FILES = client server
SRC			=	$(addprefix $(SRC_DIR)), $(addsuffix .c, $(SRC_FILES))

all : $(NAME)

$(NAME):
	@make -C ft_printf
	@mkdir -p server
server: $(NAME)
	@$(CC) $(CC_FLAGS) $(SRC_DIR)server.c $(LIBRARIE) -I $(INCLUDE) -o server/server.exec
	@echo "server compiled"

client: $(NAME)
	@$(CC) $(CC_FLAGS) $(SRC_DIR)client.c $(LIBRARIE) -I $(INCLUDE) -o server/client.exec
	@echo "client compiled"

start: client server
	@clear
	@./server/server.exec

clean:
	@make clean -C ft_printf
	@rm -rf server
fclean:
	@make fclean -C ft_printf
	@rm -rf server

re: fclean all
