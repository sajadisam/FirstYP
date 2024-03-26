ifeq ($(OS), Windows_NT) 
	INCLUDE = C:\msys64\mingw64\include\SDL2
	LDFLAGS = -lmingw32 -lSDL2main  -lSDL2 -mwindows -lm
else 
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		INCLUDE = /usr/include/SDL2
		LDFLAGS = -lSDL2main -lSDL2
	endif
	ifeq ($(UNAME_S), Darwin)
		INCLUDE = /opt/homebrew/include
		LIBS := -L /opt/homebrew/lib
		LDFLAGS = -lSDL2main -lSDL2 
	endif
endif



CC=gcc
CFLAGS = -g -I$(INCLUDE) -c 


OBJ := firstyp
SRC_DIR := src/
OBJ_DIR := bin/

SOURCE_FILES := $(wildcard $(SRC_DIR)*.c)
OBJECT_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SOURCE_FILES))

# Build the intermediate files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(@D)
	@echo file: $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

# Build the binary by linking the intermediate files
$(OBJ): $(OBJECT_FILES)
	$(CC) $^ -o bin/$(OBJ) $(LDFLAGS) $(LIBS)


clean:
	rm ./bin/*

