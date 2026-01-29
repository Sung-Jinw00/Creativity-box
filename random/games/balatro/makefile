MAKEFLAGS += -s
# === Configuration du projet ===
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Nom de l'exécutable
TARGET := balatro

# Fichiers source
SRC := NaneinfCalculator.cpp utils.cpp
HDR := balatro.hpp

# Règle principale
all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Nettoyage
clean:
	rm -f $(TARGET)

# Exécution
run: all
	./$(TARGET)
