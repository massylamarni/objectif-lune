CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./src
LDFLAGS = -lGL -lGLU -lglut -lm

SRC_DIR = src
BUILD_DIR = build

SRC = $(shell find $(SRC_DIR) -name "*.cpp")

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/prog

all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean