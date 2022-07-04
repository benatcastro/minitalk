CC = gcc
NAME = minitol
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
	@mkdir -p execs
server: $(NAME)
	@$(CC) $(CC_FLAGS) $(SRC_DIR)server.c $(LIBRARIE) -I $(INCLUDE) -o execs/server
	@echo "server compiled"

client: $(NAME)
	@$(CC) $(CC_FLAGS) $(SRC_DIR)client.c $(LIBRARIE) -I $(INCLUDE) -o execs/client
	@echo "client compiled"

sanitize:
	@$(CC_FLAGS) += $(SANITIZE)

valgrind:
	@$(CC_FLAGS) += $(VALGRIND)

start: client server
	@clear
	@./execs/server &
	@cd execs/

clean:
	@make clean -C ft_printf
	@rm -rf execs
fclean:
	@make fclean -C ft_printf
	@rm -rf execs

re: fclean all
