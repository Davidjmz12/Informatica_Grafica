CXX = g++
CXXFLAGS = -Wall -g -I./include -I./include/class -I./src -I./src/class -I./lib/armadillo-14.0.2
BIN = ./bin/
BLD = ./build/
INC = ./include/
SRC = ./src/
TST = ./tests/
LIB = ./lib/
CLS = class/


all: main

main: main.o geometric.o sphere.o linear_map.o base.o
	${CXX} ${BLD}main.o ${BLD}geometric.o  ${BLD}sphere.o ${BLD}linear_map.o ${BLD}base.o -o ${BIN}main

main.o: ${SRC}main.cpp ${INC}${CLS}geometric.hpp  
	${CXX} ${CXXFLAGS} -c ${SRC}main.cpp -o ${BLD}main.o

geometric.o: ${SRC}${CLS}geometric.cpp ${INC}${CLS}geometric.hpp 
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}geometric.cpp -o ${BLD}geometric.o

sphere.o: ${SRC}${CLS}sphere.cpp  ${INC}${CLS}geometric.hpp ${INC}${CLS}base.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}sphere.cpp -o ${BLD}sphere.o

linear_map.o: ${SRC}${CLS}linear_map.cpp ${INC}${CLS}geometric.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}linear_map.cpp -o ${BLD}linear_map.o

base.o: ${SRC}${CLS}base.cpp ${INC}${CLS}geometric.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}base.cpp -o ${BLD}base.o

clean:
	del ./build/*
