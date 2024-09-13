CXX = g++
CXXFLAGS = -Wall -g -I./include -I./include/class -I./src -I./src/class
BIN = ./bin/
BLD = ./build/
INC = ./include/
SRC = ./src/
TST = ./tests/
LIB = ./lib/
CLS = class/


all: main

main: main.o point.o vector.o 
	${CXX} ${BLD}main.o ${BLD}point.o ${BLD}vector.o -o ${BIN}main

main.o: ${SRC}main.cpp ${INC}${CLS}point.hpp ${INC}${CLS}vector.hpp 
	${CXX} ${CXXFLAGS} -c ${SRC}main.cpp -o ${BLD}main.o

point.o: ${SRC}${CLS}point.cpp ${INC}${CLS}point.hpp ${INC}${CLS}vector.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}point.cpp -o ${BLD}point.o

vector.o: ${SRC}${CLS}vector.cpp ${INC}${CLS}vector.hpp ${INC}${CLS}point.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}vector.cpp -o ${BLD}vector.o

clean:
	rm -f ${BLD}main.o ${BLD}point.o
