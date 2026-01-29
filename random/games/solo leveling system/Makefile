MAKEFLAGS += -s  # Active le mode silencieux globalement

# Définition des variables
CC              = cc
FLAGS           = -Wall -Wextra -Werror -g
HDRS            = ./includes
SRCS_MAIN       = srcs/the_system.c \
                  srcs/game_menu.c \
				  srcs/intro.c \
                  srcs/messages_utils.c \
                  srcs/player_infos.c \
                  srcs/easter_eggs.c

SRCS_LIBFT      = external_functions/libft/ft_isalpha.c \
                  external_functions/libft/ft_isupalpha.c \
                  external_functions/libft/ft_islowalpha.c \
                  external_functions/libft/ft_iswritespace.c \
                  external_functions/libft/ft_isnum_equal_al.c \
                  external_functions/libft/ft_tolower.c \
                  external_functions/libft/ft_bzero.c \
                  external_functions/libft/ft_toupper.c

SRCS_GNL        = external_functions/gnl/get_next_line_bonus.c \
                  external_functions/gnl/get_next_line_utils_bonus.c

SRCS            = $(SRCS_MAIN) $(SRCS_LIBFT) $(SRCS_GNL)

# Création d'une variable pour les fichiers objets dans le répertoire obj/
OBJDIR          = obj
OBJ_LIBFT       = $(SRCS_LIBFT:external_functions/libft/%.c=$(OBJDIR)/%.o)
OBJ_GNL         = $(SRCS_GNL:external_functions/gnl/%.c=$(OBJDIR)/%.o)
OBJ_MAIN        = $(SRCS_MAIN:srcs/%.c=$(OBJDIR)/%.o)

SRC_O           = $(OBJ_MAIN) $(OBJ_LIBFT) $(OBJ_GNL)


NAME            = arise
RM              = rm -f
CYAN            = "\033[36m"
RED             = "\033[31m"
GREEN           = "\033[32m"
RESET           = "\033[0m"

# Règle par défaut : création de l'exécutable
all: create_objdir system_creation $(NAME)

# Étape pour nettoyer le terminal
clear_function:
	@clear

# Création du répertoire obj/ s'il n'existe pas déjà
create_objdir:
	@mkdir -p $(OBJDIR)

system_creation:
	@echo $(CYAN)"Creation of the system..."$(RESET)

# Création de l'exécutable
$(NAME): $(SRC_O)
	@$(CC) $(FLAGS) $(OBJDIR)/*.o -I $(HDRS) -o $(NAME)
	@echo $(GREEN)"The system is ready !"$(RESET)

$(OBJDIR)/%.o: srcs/%.c $(HDRS)/*.h
	@$(CC) $(FLAGS) -I $(HDRS) -c $< -o $@

$(OBJDIR)/%.o: external_functions/libft/%.c $(HDRS)/*.h
	@$(CC) $(FLAGS) -I $(HDRS) -c $< -o $@

$(OBJDIR)/%.o: external_functions/gnl/%.c $(HDRS)/*.h
	@$(CC) $(FLAGS) -I $(HDRS) -c $< -o $@

# Nettoyage des objets et du répertoire obj/
clean:
	@echo $(CYAN)"Deleting all objects and the obj directory..."$(RESET)
	@$(RM) -rf $(OBJDIR)

# Nettoyage complet (objets et exécutable)
fclean: clean
	@echo $(CYAN)"The system has been deleted..."$(RESET)
	@$(RM) $(NAME)

# Récompilation depuis zéro
re: fclean all

# Sécurité des règles
.PHONY: all clean fclean re create_objdir
