# Define variable
CC = g++
CFLAGS = -std=c++17 -Wall -pedantic -g -pthread

# Name of the executable file
NAME_EXE = main

# Extensions
EXTENSION_EXE = exe

# Directory for the executable
DIR_EXE = .
LIBRARY = -L Engine\lib -lEngine
INCLUDES = -I Engine\include

# Compile executable
all:
	$(CC) $(CFLAGS) -o $(DIR_EXE)/$(NAME_EXE).$(EXTENSION_EXE) Application/main.cpp $(LIBRARY) $(INCLUDES)