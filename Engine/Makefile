############################################################
# Variable #
############################################################

CC 			= g++
CFLAGS 		= -std=c++20 -Wall -pedantic -g -pthread
SHARED 		= -shared
NO_WIN 		= -mwindows

LIBRARY 	= -L lib -lmingw32 -lSDL2main -lSDL2
INCLUDES 	= -I include

# Remove function
RM 			= del

# Directory
DIR_SOURCE 	= src
DIR_LIBRARY = lib
DIR_BINARY 	= bin
DIR_INCLUDE = include
DIR_OBJECT 	= obj

# Name
ENGINE_NAME = Engine

############################################################
# Modules #
############################################################

MODULES 	= Logger Window

Logger		= Logger Displayer
Window		= Window

############################################################
# Compilation #
############################################################

all: engine library

engine: $(MODULES)
	@echo === Engine compilation SUCCESS ===

$(MODULES):
	$(MAKE) -C src\$@ $(addsuffix .o, $($@))
	@echo === Module $@ compilation COMPLETE ===

############################################################
# Library #
############################################################

library:
	ar rcs $(DIR_LIBRARY)\$(ENGINE_NAME).lib $(foreach M, $(MODULES), $(addsuffix .o,$(addprefix obj\, $($(M)))))
	@echo === Static library : COMPLETE ===
	$(CC) $(CFLAGS) $(SHARED) $(foreach M, $(MODULES), $(addsuffix .o,$(addprefix obj\, $($(M))))) -o $(DIR_BINARY)\$(ENGINE_NAME).dll $(INCLUDES) $(LIBRARY)
	@echo === Dynamic library : COMPLETE ===

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
	@echo * "MODULES" : Compile the object of a module
	@echo * clean     : Clear all object file, the static and the dynamic library
	@echo Avaiable Modules :
	@echo $(MODULES)