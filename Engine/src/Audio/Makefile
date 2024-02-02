############################################################
# Audio #
# MODULE COMPILER #
############################################################

CC 			= g++
CFLAGS 		= -std=c++20 -Wall -pedantic -g -pthread
NO_WIN 		= -mwindows

LIBRARY 	= -L ../../lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
INCLUDES 	= -I ../../include

DIR_OBJECT 	= ../../obj

%.o: %.cpp
	$(CC) $(CFLAGS) -o $(DIR_OBJECT)\$@ -c $< $(INCLUDES) $(LIBRARY)