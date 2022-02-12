SRC_DIR:=src
BIN_DIR:=bin
OBJ_DIR:=obj
LIB_DIR:=lib

SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ:=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
LIB:=$(LIB_DIR)/libaes.a


CC=gcc
CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall -Wextra -pedantic -Wold-style-definition -std=c11 # -ggdb 
LDFLAGS  := -L$(LIB_DIR)
LDLIBS   := -laes

.PHONY: all test install clean

all: clean install test

install: $(LIB)

test: test.c $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o test

clean:
# The @ disables the echoing of the command
	@$(RM) -rv $(EXE) $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR)

#########################################

$(LIB): $(OBJ) | $(LIB_DIR)
	ar rcs $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(LIB_DIR):
	mkdir -p $@

-include $(OBJ:.o=.d) # The dash is used to silence errors if the files don't exist yet
