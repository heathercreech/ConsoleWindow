SRC_DIR := src
BUILD_DIR := build
TARGET := bin/sdl.exe

SRC_EXT := cpp
SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))

INCLUDE_PATHS = -ID:/MinGW/external_lib/include/SDL2 -I include

LIBRARY_PATHS = -LD:/MinGW/external_lib/lib -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2 -L lib

COMPILER_FLAGS = -g -Wall -Wno-write-strings -std=gnu++0x

CC = g++

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(LIBRARY_PATHS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) -c -o $@ $<
	
clean:
	$(RM) -r $(BUILD_DIR) $(TARGET)

#
#all: $(MY_LIBS) $(OBJS)
#	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(MY_LIBS) $(LINKER_FLAGS) -o $(OBJ_NAME)

#object_manager.o: object_manager.h object_manager.cpp
#	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) -o object_manager.o