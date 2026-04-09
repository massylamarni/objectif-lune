CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./src
LDFLAGS = -lGL -lGLU -lglut -lm

SRC_DIR = src
ASSET_DIR = assets/models
BUILD_DIR = build

SRC = $(shell find $(SRC_DIR) -name "*.cpp")
ASSET_SRC = \
	$(ASSET_DIR)/color_palette.c

SRC_OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
ASSET_OBJ = $(patsubst $(ASSET_DIR)/%.cpp,$(BUILD_DIR)/$(ASSET_DIR)/%.o,$(filter %.cpp,$(ASSET_SRC))) \
	$(patsubst $(ASSET_DIR)/%.c,$(BUILD_DIR)/$(ASSET_DIR)/%.o,$(filter %.c,$(ASSET_SRC)))

OBJ = $(SRC_OBJ) $(ASSET_OBJ)

TARGET = $(BUILD_DIR)/prog

all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(ASSET_DIR)/%.o: $(ASSET_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(ASSET_DIR)/%.o: $(ASSET_DIR)/%.c
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean