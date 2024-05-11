# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++20

# Source files
SRC = $(wildcard src/game/*.cpp src/utils/*.cpp src/main.cpp)

# Object files
OBJ = $(patsubst src/%,build/%,$(SRC:.cpp=.o))

# Executable name
EXEC = game

# Default rule
all: directories $(EXEC)

# Rule to create the necessary directories
directories:
	mkdir -p build/game
	mkdir -p build/utils

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(EXEC)
