CC=gcc
CPPFLAGS := -Iinclude -MMD -MP # -I is a preprocessor flag, not a compiler flag
CFLAGS   := -Wall -Wextra -pedantic -Wold-style-definition  -ggdb -std=c11
LDFLAGS  := -Llib              # -L is a linker flag
LDLIBS   := -lm                # Left empty if no libs are needed

SRC_DIR:=src
OBJ_DIR:=obj
BIN_DIR:=.

EXE:=$(BIN_DIR)/aes
SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(EXE) $(OBJ_DIR) # The @ disables the echoing of the command

-include $(OBJ:.o=.d) # The dash is used to silence errors if the files don't exist yet
