# Define variable
CC = g++
CFLAGS = -std=c++17 -Wall -pedantic -g -pthread

# Name of the executable file
NAME_EXE = main

# Extensions
EXTENSION_EXE = exe

# Directory for the executable
#DIR_EXE = Application\bin
DIR_EXE = Application\bin
LIBRARY = -L Engine\lib -lEngine -lmingw32 -lSDL2main -lSDL2 # ATTENTION A L'ORDRE DES INCLUSION DES LIBRAIRIES
INCLUDES = -I Engine\include -I Engine\include\External
GLAD_SRC = Engine\src\External\GLAD\glad.c

# Compile executable
all:
	$(CC) $(CFLAGS) -o $(DIR_EXE)/$(NAME_EXE).$(EXTENSION_EXE) Application/main.cpp $(GLAD_SRC) $(LIBRARY) $(INCLUDES)
# ATTENTION A L'ORDRE DES LIB ET INCLUDES