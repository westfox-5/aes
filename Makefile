SRC_DIR:=src
BIN_DIR:=bin
OBJ_DIR:=obj
INC_DIR:=include
DIST_DIR:=dist

TEST:=test
AES:=aes

SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ:=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
LIB:=lib$(AES).a

CC=gcc
CPPFLAGS := -I$(INC_DIR) -MMD -MP
CFLAGS   := -Wall -Wextra -pedantic -Wold-style-definition -std=c11 # -ggdb 
LDFLAGS  := -L$(DIST_DIR)
LDLIBS   := -l$(AES)


##########   TARGETS   ###############################
.PHONY: all clean $(AES) $(TEST)

all: clean $(AES)

clean:
	@$(RM) -rv $(AES) $(BIN_DIR) $(OBJ_DIR) $(DIST_DIR) $(DIST_DIR)
	@$(RM) -rv $(TEST) $(TEST).d

$(AES): $(LIB)

$(TEST): $(TEST).c $(AES)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $(TEST) $(LDFLAGS) $(LDLIBS)
######################################################


$(LIB): $(OBJ) | $(DIST_DIR)
	ar rcvs $@ $^
	mv $(LIB) $(DIST_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(DIST_DIR):
	mkdir -p $@

-include $(OBJ:.o=.d) # The dash is used to silence errors if the files don't exist yet
