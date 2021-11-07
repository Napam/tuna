CXX = g++-11 
CXXFLAGS = -std=c++20 -Ofast -Winvalid-pch
OUT_FILE = simpleapp.out
MAIN_FILE = main.cpp
PCH_FILE = include/tunapch.hpp
LINKS = -lSDL2 -lSDL2_ttf -lSDL2_gfx
BUILD_DIR = build
INCLUDES = -Iinclude

MAKEFLAGS += -j$(shell nproc --all)

SOURCES = $(wildcard states/*.cpp) \
		  $(wildcard classes/*.cpp) \
		  $(wildcard utils/*.cpp)

OBJECTS = $(BUILD_DIR)/$(MAIN_FILE:.cpp=.o) \
		  $(shell echo $(SOURCES) | sed -E "s|\w+/(\w+).cpp|$(BUILD_DIR)/\1.o|g")

default: $(OUT_FILE)

$(OUT_FILE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(INCLUDES) $(LINKS) -o $@

VPATH = states classes utils

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 

pch: $(PCH_FILE)
	$(CXX) $(CXXFLAGS) $(PCH_FILE) 

.PHONY: clean

clean:
	rm -f $(OUT_FILE) build/*.o