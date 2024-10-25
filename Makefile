# Define variable
CC = g++
CFLAGS = -std=c++20 -Wall -pedantic -g -pthread -O2 -ftree-vectorize -march=native -DDEBUG

# Name of the executable file
NAME_EXE = main

# Extensions
EXTENSION_EXE = exe

# Directory for the executable
DIR_EXE = Application\bin
LIBRARY = -L Engine\lib -lEngine -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lfreetype # ATTENTION A L'ORDRE DES INCLUSION DES LIBRAIRIES
INCLUDES = -I Engine\include -I Engine\include\External
GLAD_SRC = Engine\src\External\GLAD\glad.c

# Orange path
ORA_LIB = -L Ora\lib -lOrange -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lfreetype # ATTENTION A L'ORDRE DES INCLUSION DES LIBRAIRIES
ORA_INC = -I Ora\inc -I Ora\inc\External
ORA_GLAD = Ora\src\glad\glad.c

# Compile executable
all:
	$(CC) $(CFLAGS) -o $(DIR_EXE)/$(NAME_EXE).$(EXTENSION_EXE) Application/main.cpp $(GLAD_SRC) $(LIBRARY) $(INCLUDES)

ecs:
	$(CC) $(CFLAGS) -o $(DIR_EXE)/ecs_test.$(EXTENSION_EXE) Application/ecs_test.cpp $(GLAD_SRC) $(LIBRARY) $(INCLUDES)

orange:
	$(CC) $(CFLAGS) -o $(DIR_EXE)/orange.$(EXTENSION_EXE) Application/orange.cpp $(ORA_GLAD) $(ORA_LIB) $(ORA_INC)

# ATTENTION A L'ORDRE DES LIB ET INCLUDES