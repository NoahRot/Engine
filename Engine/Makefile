############################################################
# Variable #
############################################################

CC = g++
CFLAGS = -std=c++17 -Wall -pedantic -g -pthread
SHARED = -shared
NO_WIN = -mwindows

LIBRARY = -L lib
INCLUDES = -I include

# Remove function
RM = del

# Directory
DIR_SOURCE = src
DIR_LIBRARY = lib
DIR_BINARY = bin
DIR_INCLUDE = include
DIR_OBJECT = obj

# Name
ENGINE_NAME = Engine


############################################################
# Compilation #
############################################################

ENGINE_OBJECT = Engine Test Window

engine: $(addsuffix .o, $(ENGINE_OBJECT))
	@echo Object compilation : COMPLETE

%.o: $(DIR_SOURCE)\%.cpp
	$(CC) $(CFLAGS) -o $(DIR_OBJECT)\$@ -c $< $(INCLUDES) $(LIBRARY)

############################################################
# Library #
############################################################
library:
	ar rcs $(DIR_LIBRARY)\$(ENGINE_NAME).lib $(addsuffix .o,$(addprefix obj\, $(ENGINE_OBJECT)))
	@echo Static library : COMPLETE
	$(CC) $(CFLAGS) $(SHARED) $(addsuffix .o,$(addprefix obj\, $(ENGINE_OBJECT))) -o $(DIR_BINARY)\$(ENGINE_NAME).dll $(INCLUDES) $(LIBRARY)
	@echo Dynamic library : COMPLETE

############################################################
# Clean #
############################################################

clean:
	$(RM) $(DIR_OBJECT)\*.o
	$(RM) $(DIR_LIBRARY)\$(ENGINE_NAME).lib
	$(RM) $(DIR_BINARY)\$(ENGINE_NAME).dll

############################################################
# Help #
############################################################
help:
	@echo Makefile methods to compile the engine :
	@echo * engine    : Compile the object of the engine
	@echo * library   : Compile the static and dynamic libraries
	@echo * clean     : Clear all object file, the static and the dynamic library