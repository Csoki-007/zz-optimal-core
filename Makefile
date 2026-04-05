# Fordító
CXX = g++
CXXFLAGS = -Wall -g

# Könyvtárak
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BUILD_DIR = build

# Forrás- és objektumfájlok
SOURCES = $(filter-out $(SRC_DIR)/esp32_main.cpp,$(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Célfájl
TARGET = $(BUILD_DIR)/main.exe

# Alapértelmezett cél
all: $(TARGET)

# Linkelés
$(TARGET): $(OBJECTS)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Fordítás
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Tisztítás
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

# Egyéb
.PHONY: all clean run

run: $(TARGET)
	$(TARGET)
