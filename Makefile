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

test: ${BIN}test_geometric.exe ${BIN}test_matrix.exe

${BIN}main.exe: ${BLD}main.o ${BLD}geometric.o ${BLD}sphere.o ${BLD}linear_map.o ${BLD}base.o ${BLD}matrix.o
	${CXX} ${BLD}main.o ${BLD}geometric.o  ${BLD}sphere.o ${BLD}linear_map.o ${BLD}base.o ${BLD}matrix.o -o ${BIN}main.exe

${BLD}main.o: ${SRC}main.cpp ${INC}${CLS}geometric.hpp  
	${CXX} ${CXXFLAGS} -c ${SRC}main.cpp -o ${BLD}main.o

${BLD}geometric.o: ${SRC}${CLS}geometric.cpp ${INC}${CLS}geometric.hpp  
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}geometric.cpp -o ${BLD}geometric.o

${BLD}sphere.o: ${SRC}${CLS}sphere.cpp  ${INC}${CLS}geometric.hpp ${INC}${CLS}base.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}sphere.cpp -o ${BLD}sphere.o

${BLD}linear_map.o: ${SRC}${CLS}linear_map.cpp ${INC}${CLS}geometric.hpp ${INC}${CLS}matrix.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}linear_map.cpp -o ${BLD}linear_map.o

${BLD}base.o: ${SRC}${CLS}base.cpp ${INC}${CLS}geometric.hpp ${INC}${CLS}matrix.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}base.cpp -o ${BLD}base.o

${BLD}matrix.o: ${SRC}${CLS}matrix.cpp ${INC}${CLS}matrix.hpp ${INC}${CLS}geometric.hpp
	${CXX} ${CXXFLAGS} -c ${SRC}${CLS}matrix.cpp -o ${BLD}matrix.o




# ----------------------------------	TESTS	------------------------------------------------
# GEOMETRIC TESTS
${BIN}test_geometric.exe: ${BLD}test_geometric.o ${BLD}geometric.o
	${CXX} ${BLD}test_geometric.o ${BLD}geometric.o -o ${BIN}test_geometric.exe

${BLD}test_geometric.o: ${TST}test_geometric.cpp ${INC}${CLS}geometric.hpp ${INC}${CLS}test.hpp
	${CXX} ${CXXFLAGS} -c ${TST}test_geometric.cpp -o ${BLD}test_geometric.o

# MATRIX TESTS
${BIN}test_matrix.exe: ${BLD}test_matrix.o ${BLD}matrix.o ${BLD}geometric.o
	${CXX} ${BLD}test_matrix.o ${BLD}matrix.o ${BLD}geometric.o -o ${BIN}test_matrix.exe

${BLD}test_matrix.o: ${TST}test_matrix.cpp ${INC}${CLS}matrix.hpp ${INC}${CLS}test.hpp
	${CXX} ${CXXFLAGS} -c ${TST}test_matrix.cpp -o ${BLD}test_matrix.o

# LINEAR MAP TESTS
${BIN}test_linear_map.exe: ${BLD}test_linear_map.o ${BLD}linear_map.o ${BLD}geometric.o ${BLD}base.o ${BLD}matrix.o
	${CXX} ${BLD}test_linear_map.o ${BLD}linear_map.o ${BLD}geometric.o ${BLD}base.o ${BLD}matrix.o -o ${BIN}test_linear_map.exe

${BLD}test_linear_map.o: ${TST}test_linear_map.cpp ${INC}${CLS}linear_map.hpp ${INC}${CLS}test.hpp ${INC}${CLS}base.hpp ${INC}${CLS}geometric.hpp
	${CXX} ${CXXFLAGS} -c ${TST}test_linear_map.cpp -o ${BLD}test_linear_map.o


clean:
	del ./build/*
