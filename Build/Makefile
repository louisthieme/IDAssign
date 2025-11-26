# MAKEFILE SimpleDB

# Compiler
CXX=g++

# Compiler flags
CXXFLAGS = -g
DEBUGFLAGS = -Wall

# Project name
PROJ_NAME = IDASSIGN

# Source files
SRC		=	main.cpp IDAssign.cpp
LIB		=	LogSys.cpp FileStream.cpp BasicFileIO.cpp

# Add prefix folder
SOURCE_PREFIX	=	../
DIRLIB_PREFIX	=	../lib/

SRC_PREFIX		=	$(addprefix $(SOURCE_PREFIX), $(SRC))
LIB_PREFIX		=	$(addprefix $(DIRLIB_PREFIX), $(LIB))

# Object files
SRC_O			=	$(SRC:.cpp=.o) 
LIB_O			=	$(LIB:.cpp=.o)

SRC_PREFIX_O	=	$(SRC_PREFIX:.cpp=.o)
LIB_PREFIX_O	=	$(LIB_PREFIX:.cpp=.o)

#all
all: executable
	$(PROJ_NAME).exe

#Build
executable: object_files
	$(CXX) $(CXXFLAGS) $(SRC_O) $(LIB_O) -o $(PROJ_NAME)

object_files:
	$(CXX) $(CXXFLAGS) $(SRC_PREFIX) -c
	$(CXX) $(CXXFLAGS) $(LIB_PREFIX) -c
	

#clean
#use 'del'  for windows instead of 'rm -f'
.PHONY: clean
clean: 
	del $(SRC_O) $(LIB_O)

