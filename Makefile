CXX = g++
CXXFLAGS = -Wall -g -I./include -I./include/class -I./src -I./src/class
BIN = ./bin/
BLD = ./build/
INC = ./include/
SRC = ./src/
TST = ./tests/
LIB = ./lib/
CLS = class/


all: ${BIN}main.exe

test: ${BIN}test_geometric.exe

${BIN}main.exe: ${BLD}main.o ${BLD}geometric.o ${BLD}sphere.o ${BLD}linear_map.o ${BLD}base.o ${BLD}matrix.o
	${CXX} ${BLD}main.o ${BLD}geometric.o  ${BLD}sphere.o ${BLD}linear_map.o ${BLD}base.o ${BLD}matrix.o -o ${BIN}main.exe

${BLD}main.o: ${SRC}main.cpp ${INC}${CLS}geometric.hpp  
	${CXX} ${CXXFLAGS} -c ${SRC}main.cpp -o ${BLD}main.o

${BLD}geometric.o: ${SRC}${CLS}geometric.cpp ${INC}${CLS}geometric.hpp 
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}geometric.cpp -o ${BLD}geometric.o

${BLD}sphere.o: ${SRC}${CLS}sphere.cpp  ${INC}${CLS}geometric.hpp ${INC}${CLS}base.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}sphere.cpp -o ${BLD}sphere.o

${BLD}linear_map.o: ${SRC}${CLS}linear_map.cpp ${INC}${CLS}geometric.hpp ${INC}matrix.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}linear_map.cpp -o ${BLD}linear_map.o

${BLD}base.o: ${SRC}${CLS}base.cpp ${INC}${CLS}geometric.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}base.cpp -o ${BLD}base.o

${BLD}matrix.o: ${SRC}matrix.cpp ${INC}matrix.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}matrix.cpp -o ${BLD}matrix.o


${BIN}test_geometric.exe: ${BLD}test_geometric.o geometric.o
	${CXX} ${BLD}test_geometric.o ${BLD}geometric.o -o ${BIN}test_geometric

${BLD}test_geometric.o: ${TST}test_geometric.cpp ${INC}${CLS}geometric.hpp
	${CXX} ${CXXFLAGS} -c ${TST}test_geometric.cpp -o ${BLD}test_geometric.o


clean:
	del ./build/*
