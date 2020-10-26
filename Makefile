CC = g++
CPPFLAGS = -Iinclude -MMD -MP
CFLAGS = -g -std=c++2a -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
BIN := $(BIN_DIR)/exe

.PHONY: clean default run

default: $(BIN)

run:
	./bin/exe

$(BIN): $(OBJ)
		$(CC) -o $@ $^ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
		rm -rf $(OBJ_DIR)/*
			rm -rf $(BIN_DIR)/*

-include $(OBJ:.o=.d)
