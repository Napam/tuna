CXX = gcc
CXXFLAGS = -Ofast
BUILD_DIR ?= build
INCLUDES = -Iinclude

OUT_FILE = glad.o
SOURCE = src/glad.c

default: $(OUT_FILE)

$(OUT_FILE): | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SOURCE) -o $(BUILD_DIR)/$@

$(BUILD_DIR):
	mkdir build