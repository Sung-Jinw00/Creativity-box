MAKEFLAGS += -s

CC = cc

FLAGS = -Wall -Wextra -Werror -g

NAME = libasprintf.a
# NAME = asprintf

LIBFT = ft_asprintf.h

FILES = $(shell find ./ -type f -name '*.c')

OBJ_DIR = obj

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(FILES))

CYAN	= "\033[36m"
GREEN	= "\033[32m"
RESET	= "\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: message ${NAME}

# message :
# 	@echo $(GREEN)"Exécutable créé !"$(RESET)
message :
	@echo $(GREEN)"lib créée !"$(RESET)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -I ./ -I lib/libft.a -c $< -o $@

# $(NAME): $(OBJS)
# 	$(CC) $(FLAGS) -o $@ $^ -L ./lib -lft
${NAME}: ${OBJS}
	ar rcs $@ $^

clean:
	@echo $(GREEN)"objets supprimés !"$(RESET)
	rm -f ${OBJS}

fclean: clean
	@echo $(GREEN)"dossier objet et lib supprimés !"$(RESET)
	rm -rf ${OBJ_DIR}
	rm -f $(NAME)

bonus: $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
