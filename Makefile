CC=cc
CFLAGS=-O2 -Wall -Wextra
INC=-Iinclude -Ideps/assimp/include -Ideps/assimp/build/include
LIB=$(shell pkg-config --libs glfw3) $(shell pkg-config --libs assimp) -lm
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, %.o, $(SRC))
BIN=quake_movement

default: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< $(INC)

clean:
	rm -f $(BIN) $(OBJ)
