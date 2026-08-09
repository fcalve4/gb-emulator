CC := gcc
CSTD := -std=c17

SDL2_DIR := C:/SDL2-2.32.10/x86_64-w64-mingw32
INCLUDES := -I$(SDL2_DIR)/include -Iinclude -Isrc
LIBS     := -L$(SDL2_DIR)/lib -lmingw32 -lSDL2main -lSDL2 -mwindows

# Compiler flags
CFLAGS := $(CSTD) -Wall -Wextra -g $(INCLUDES)

SRC_DIR := src
OBJ_DIR := obj
BIN     := emulator.exe

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	del /Q $(OBJ_DIR)\*.o $(BIN) 2>nul || true

run: all
	./$(BIN)