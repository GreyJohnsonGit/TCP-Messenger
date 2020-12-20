CC = g++
CPPFLAGS = -Iinclude -MMD -MP -pthread -std=c++11
CFLAGS = -g -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
BIN := $(BIN_DIR)/peerProcess

.PHONY: clean default run

default: $(BIN)

$(BIN): $(OBJ)
		$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
		rm -rf $(OBJ_DIR)/*
		rm -rf $(BIN_DIR)/*

-include $(OBJ:.o=.d)
