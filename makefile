CC = g++

INC = include
SRC = src
OBJ = obj
BIN = bin

CFLAGS = -Wall -Wextra -I$(INC) -std=c++17 -g

$(BIN)/binary: $(OBJ)/memlog.o $(OBJ)/fita.o $(OBJ)/heap.o $(OBJ)/main.o
	$(CC) -o $(BIN)/binary $(OBJ)/memlog.o $(OBJ)/fita.o $(OBJ)/heap.o $(OBJ)/main.o

$(OBJ)/memlog.o: $(INC)/memlog.hpp $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -c $(SRC)/memlog.cpp -o $(OBJ)/memlog.o

$(OBJ)/fita.o: $(INC)/memlog.hpp $(INC)/fita.hpp $(SRC)/fita.cpp
	$(CC) $(CFLAGS) -c $(SRC)/fita.cpp -o $(OBJ)/fita.o

$(OBJ)/heap.o: $(INC)/memlog.hpp $(INC)/heap.hpp $(SRC)/heap.cpp
	$(CC) $(CFLAGS) -c $(SRC)/heap.cpp -o $(OBJ)/heap.o

$(OBJ)/main.o: $(INC)/memlog.hpp $(INC)/heap.hpp $(SRC)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

test: $(OBJ)/memlog.o $(OBJ)/fita.o $(OBJ)/heap.o $(OBJ)/test.o
	$(CC) -o $(BIN)/test $(OBJ)/memlog.o $(OBJ)/fita.o $(OBJ)/heap.o $(OBJ)/test.o -lgtest

$(OBJ)/test.o: $(INC)/memlog.hpp $(INC)/heap.hpp $(SRC)/test.cpp
	$(CC) $(CFLAGS) -c $(SRC)/test.cpp -o $(OBJ)/test.o

clean:
	rm -rI $(OBJ)/* $(BIN)/binary $(BIN)/test
