SRC_DIR   := ./src
BUILD_DIR := ./build

all_obj: lexer_obj utils_obj

#### Lexer objects creation #####

LEXER_SRC_DIR   := $(SRC_DIR)/lexer
LEXER_BUILD_DIR := $(BUILD_DIR)/lexer

lexer_obj: make_lexer_dir $(LEXER_BUILD_DIR)/lexer.o $(LEXER_BUILD_DIR)/lexer_helper.o

make_lexer_dir:
		mkdir -p $(LEXER_BUILD_DIR)

$(LEXER_BUILD_DIR)/lexer.o: $(LEXER_SRC_DIR)/lexer.c
		gcc -c $(LEXER_SRC_DIR)/lexer.c -o $(LEXER_BUILD_DIR)/lexer.o

$(LEXER_BUILD_DIR)/lexer_helper.o: $(LEXER_SRC_DIR)/lexer_helper.c
		gcc -c $(LEXER_SRC_DIR)/lexer_helper.c -o $(LEXER_BUILD_DIR)/lexer_helper.o


##### Util objects creation #####

UTILS_SRC_DIR   := $(SRC_DIR)
UTILS_BUILD_DIR := $(BUILD_DIR)

utils_obj: $(UTILS_BUILD_DIR)/utils.o

$(UTILS_BUILD_DIR)/utils.o: $(UTILS_SRC_DIR)/utils.c
		gcc -c $(UTILS_SRC_DIR)/utils.c -o $(UTILS_BUILD_DIR)/utils.o


clean_obj:
		rm -fr build/*
