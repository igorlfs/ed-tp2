CC = g++

INC = include
SRC = src
OBJ = obj
BIN = bin

EXE = $(BIN)/binary

CFLAGS = -Wall -Wextra -I$(INC) -std=c++17 -g

$(EXE): $(OBJ)/fita.o $(OBJ)/heap.o $(OBJ)/main.o
	$(CC) -o $(EXE) $(OBJ)/*.o

$(OBJ)/fita.o: $(INC)/fita.hpp $(SRC)/fita.cpp
	$(CC) $(CFLAGS) -c $(SRC)/fita.cpp -o $(OBJ)/fita.o

$(OBJ)/heap.o: $(INC)/heap.hpp $(SRC)/heap.cpp
	$(CC) $(CFLAGS) -c $(SRC)/heap.cpp -o $(OBJ)/heap.o

$(OBJ)/main.o: $(INC)/heap.hpp $(SRC)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

clean:
	rm -rI $(OBJ)/* $(BIN)/*
