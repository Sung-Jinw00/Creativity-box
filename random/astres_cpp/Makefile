MAKEFLAGS += -s  # Active le mode silencieux globalement

# Définition des variables
C++				= c++
HDRS			= ./includes
FLAGS			= -Wall -Wextra -Werror -std=c++98 -g -I $(HDRS)

SRCS			=  main.cpp AAstre.cpp
SRC_O			= $(SRCS:.cpp=.o)
EXEC			= Astres
RM				= rm -f
CYAN			= "\033[36m"
RED				= "\033[31m"
GREEN			= "\033[32m"
RESET			= "\033[0m"

# Règle par défaut : création de l'exécutable
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(SRC_O)
	@echo $(CYAN)"Création de l'exécutable $(EXEC)..."$(RESET)
	@$(C++) $(FLAGS) $(SRC_O) -o $(EXEC)
	@echo $(GREEN)"Exécutable $(EXEC) créé !"$(RESET)

# Compilation des fichiers sources en objets
%.o: %.cpp
	@echo $(CYAN)"Compilation de $<..."$(RESET)
	@$(C++) $(FLAGS) -c $< -o $@

# Nettoyage des objets
clean:
	@echo $(CYAN)"Suppression des fichiers objets..."$(RESET)
	@$(RM) *.o

# Nettoyage complet
fclean: clean
	@echo $(CYAN)"Suppression de l'exécutable..."$(RESET)
	@$(RM) $(EXEC) 

# Récompilation depuis zéro
re: fclean all

# Sécurité des règles
.PHONY: all clean fclean re
