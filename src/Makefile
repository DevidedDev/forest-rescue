#
COMPILER = g++

#.cpp files:
FILES = *.cpp

#
EXECUTABLE_NAME = executable


#LINKER FLAGS - what libraries we're linking?
LINKER_FLAGS = -lSDL2 -lSDL2_image


#COMPILER FLAGS - extra compilation options
# -w suppresses all warnings
COMPILER_FLAGS = -w


make_executable : ${FILES}
	${COMPILER} ${FILES} ${COMPILER_FLAGS} ${LINKER_FLAGS} -o ${EXECUTABLE_NAME}
 
clear:
	rm executables