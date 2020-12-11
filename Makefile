CC = g++
CPPFLAGS = -Iinclude -MMD -MP -pthread -std=c++2a
CFLAGS = -g -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
REL_DIR = release
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
BIN := $(BIN_DIR)/tb.exe
REL := $(REL_DIR)/tb.exe

.PHONY: clean default run

default: $(BIN)

$(BIN): $(OBJ)
		$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^
		cp $(BIN) $(REL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
		rm -rf $(OBJ_DIR)/*
		rm -rf $(BIN_DIR)/*

-include $(OBJ:.o=.d)
