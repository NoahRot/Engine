############################################################
# Variable #
############################################################

CC 			= g++
CFLAGS 		= -std=c++20 -Wall -pedantic -g -pthread
SHARED 		= -shared
NO_WIN 		= -mwindows

LIBRARY 	= -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
INCLUDES 	= -I include
INCLUDES_EXTERNAL = -I include\External

# Remove function
RM 			= del

# Directory
DIR_SOURCE 	= src
DIR_LIBRARY = lib
DIR_BINARY 	= bin
DIR_INCLUDE = include
DIR_OBJECT 	= obj
DIR_EXTERNAL = External

# Name
ENGINE_NAME = Engine

# Gald
GLAD_SRC = $(DIR_SOURCE)/$(DIR_EXTERNAL)/glad/glad.c

#**********************************************************#
# ONLY TO SIMPLIFY | SHOULD BE ERASE FOR FINAL RELEASE #
#**********************************************************#

DIR_BIN_PROJECT = ..\Application\bin

#**********************************************************#
# END #
#**********************************************************#

############################################################
# Modules #
############################################################

MODULES 	= Core Logger Event Graphic Audio

Core		= Core Window Timer CoreFnc
Logger		= Logger Displayer
Event		= Event Keyboard Mouse
Graphic		= Texture Renderer Shader VertexArray VertexBuffer IndexBuffer
Audio 		= Sound Music Audio

############################################################
# Compilation #
############################################################

all: engine library

engine: $(MODULES)
	@echo === Engine compilation SUCCESS ===

$(MODULES):
	$(MAKE) -C $(DIR_SOURCE)\$@ $(addsuffix .o, $($@))
	@echo === Module $@ compilation COMPLETE ===

############################################################
# Library #
############################################################

library:
	ar rcs $(DIR_LIBRARY)\$(ENGINE_NAME).lib $(foreach M, $(MODULES), $(addsuffix .o,$(addprefix obj\, $($(M)))))
	@echo === Static library : COMPLETE ===
	$(CC) $(CFLAGS) $(SHARED) $(foreach M, $(MODULES), $(addsuffix .o,$(addprefix obj\, $($(M))))) -o $(DIR_BINARY)\$(ENGINE_NAME).dll $(GLAD_SRC) $(INCLUDES) $(INCLUDES_EXTERNAL) $(LIBRARY)
	@copy $(DIR_BINARY)\$(ENGINE_NAME).dll $(DIR_BIN_PROJECT)
	@echo === Dynamic library : COMPLETE ===

############################################################
# Clean #
############################################################

clean:
	$(RM) $(DIR_OBJECT)\*.o
	$(RM) $(DIR_LIBRARY)\$(ENGINE_NAME).lib
	$(RM) $(DIR_BIN_PROJECT)\$(ENGINE_NAME).dll
	$(RM) $(DIR_BINARY)\$(ENGINE_NAME).dll

############################################################
# Help #
############################################################

help:
	@echo Makefile methods to compile the engine :
	@echo * all       : Compile everything
	@echo * engine    : Compile the object of the engine
	@echo * library   : Compile the static and dynamic libraries
	@echo * "MODULES" : Compile the object of a module (you can find the avaiable modules bellow)
	@echo * clean     : Clear all object file, the static and the dynamic library
	@echo Avaiable Modules :
	@echo $(MODULES)