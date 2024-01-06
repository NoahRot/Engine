############################################################
# Logger #
############################################################

CC 			= g++
CFLAGS 		= -std=c++20 -Wall -pedantic -g -pthread
SHARED 		= -shared
NO_WIN 		= -mwindows

LIBRARY 	= -L ../../lib
INCLUDES 	= -I ../../include

DIR_SOURCE 	= src
DIR_LIBRARY = ../../lib
DIR_BINARY 	= ../../bin
DIR_INCLUDE = ../../include
DIR_OBJECT 	= ../../obj

LOGGER_OBJECT = Displayer Logger

%.o: %.cpp
	$(CC) $(CFLAGS) -o $(DIR_OBJECT)\$@ -c $< $(INCLUDES) $(LIBRARY)