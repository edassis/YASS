SRC_PATH = src
BUILD_PATH = build

#OBJS specifies which files to compile as part of the project
SRCS_NAMES = main.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\msys64\mingw64\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\msys64\mingw64\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
# COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS = -Wall -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = MySDLProgram

#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

all : $(SRC_PATH)/$(SRCS_NAMES) 
	$(CC) $(SRC_PATH)/$(SRCS_NAMES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_PATH)/$(OBJ_NAME)