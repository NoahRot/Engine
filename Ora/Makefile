# ===========================================================
# DEFINE VARIABLES
# ===========================================================

# Define compilator and flags
CC = g++
CFLAGS = -std=c++20 -Wall -pedantic -g -pthread -O2 -ftree-vectorize -march=native -DDEBUG
SHARED = -shared
NO_WIN = -mwindows

# Name
ENGINE_NAME = Orange

# Remove function
RM = del

# Directories
DIR_SRC = src
DIR_LIB = lib
DIR_BIN = bin
DIR_INC = inc
DIR_OBJ = $(DIR_BIN)\obj
DIR_EXT = $(DIR_INC)\External

LIBRARY = -L lib -lOrange -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lfreetype # ATTENTION A L'ORDRE DES INCLUSION DES LIBRAIRIES
INCLUDES = -I $(DIR_INC) -I $(DIR_EXT)

# *** SHOULD BE REMOVE LATER ***
DIR_BIN_PROJECT = ..\Application\bin
# *** SHOULD BE REMOVE LATER ***

# Gald
GLAD_SRC = src/glad/glad.c

# Source and object files
SUB_DIR = $(wildcard $(DIR_SRC)/*/.)
SOURCE = $(foreach DIR, $(SUB_DIR), $(wildcard $(DIR)/*.cpp))
OBJECT = $(patsubst %.cpp,%.o,$(SOURCE))
COBJECT = $(foreach OBJ, $(OBJECT), $(DIR_OBJ)/$(notdir $(OBJ)))

# Modules
MODULE = $(subst /.,,$(subst $(DIR_SRC)/,,$(SUB_DIR)))

# Define new line command
define \n


endef

# ===========================================================
# COMPILE ALL MODULES AND THE LIBRARIES
# ===========================================================
all: $(MODULE) library

# ===========================================================
# COMPILE THE LIBRARIES
# ===========================================================
library:
	@echo Static library compilation...
	ar rcs $(DIR_LIB)\$(ENGINE_NAME).lib $(COBJECT)
	@echo Static library compilation : SUCCESS
	@echo Dynamic library compilation...
	$(CC) $(CFLAGS) $(SHARED) $(COBJECT) -o $(DIR_BIN)\$(ENGINE_NAME).dll $(GLAD_SRC) $(INCLUDES) $(LIBRARY)
# *** SHOULD BE REMOVE LATER ***
	@copy $(DIR_BIN)\$(ENGINE_NAME).dll $(DIR_BIN_PROJECT)
# *** SHOULD BE REMOVE LATER ***
	@echo Dynamic library compilation : SUCCESS

# ===========================================================
# COMPILE ALL MODULES
# ===========================================================
modules: $(MODULE)

# ===========================================================
# COMPILE ONE MODULE
# ===========================================================
$(MODULE):
	@echo Module $@ compilation...
	$(foreach FILE, $(patsubst %.cpp,%.o,$(wildcard $(DIR_SRC)/$@/*.cpp)), $(CC) $(CFLAGS) -o $(DIR_OBJ)\$(notdir $(FILE)) -c $(patsubst %.o,%.cpp,$(FILE)) $(INCLUDES) $(LIBRARY) ${\n})
	@echo Module $@ compilation : SUCCESS

# ===========================================================
# CLEAR OBJECT FILES,, THE STATIC AND THE DYNAMIC LIBRARIES
# ===========================================================
clear:
	$(RM) $(DIR_OBJ)\*.o
	$(RM) $(DIR_LIB)\$(ENGINE_NAME).lib
	$(RM) $(DIR_BIN_PROJECT)\$(ENGINE_NAME).dll
	$(RM) $(DIR_BIN)\$(ENGINE_NAME).dll

# ===========================================================
# PRINT HELP FUNCTIONS FOR THE USER
# ===========================================================
help:
	@echo + all : Compile all modules, the static and the dynamic library
	@echo + library : Compile the static and the dynamic library
	@echo + modules : Compile all modules
	@echo + "Module" : Compile a module. Here is the list of all the modules:
	$(foreach MODE,$(MODULE), @echo   - $(MODE)${\n})
	@echo + clear : Delete the object files, the static and the dynamic library 