# Nom du compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -std=c++17

# Liste des fichiers sources
SRCS = main.cpp $(wildcard ./MiniBim/*.cpp)

# Nom de l'exécutable
TARGET = tp4

# Liste des fichiers objets (automatique à partir des sources)
OBJS = $(SRCS:.cpp=.o)

# Règle par défaut
all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Règle pour construire l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle générique pour compiler les fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyer les fichiers objets et l'exécutable
clean:
	del /Q *.o $(TARGET).exe MiniBim\*.o

.PHONY: all clean