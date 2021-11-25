CXX = g++-11
CXXFLAGS = -std=c++20 -Ofast -Winvalid-pch
OUT_FILE = simpleapp.out
MAIN_FILE = main.cpp
PCH_FILE = include/tunapch.hpp
LINKS = -lSDL2 -lSDL2_ttf -lSDL2_gfx -ldl
INCLUDES = -Iinclude
VENDOR = vendor
export BUILD_DIR = build

MAKEFLAGS += -j$(shell nproc --all)

SOURCES = $(wildcard states/*.cpp) \
		  $(wildcard classes/*.cpp) \
		  $(wildcard utils/*.cpp)

OBJECTS = $(BUILD_DIR)/$(MAIN_FILE:.cpp=.o) \
		  $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o))) \
		  $(VENDOR)/Glad/$(BUILD_DIR)/glad.o

default: $(OUT_FILE)

run: $(OUT_FILE)
	./$(OUT_FILE)

$(OUT_FILE): $(OBJECTS) $(PCH_FILE)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(INCLUDES) $(LINKS) -o $@

VPATH = states classes utils

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(PCH_FILE).gch: $(PCH_FILE)
	$(CXX) $(CXXFLAGS) $(PCH_FILE) 

$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir build
	$(MAKE) -C vendor/Glad

.PHONY: clean glad 

clean:
	rm -rf $(OUT_FILE) \
		  $(BUILD_DIR) \
		  $(PCH_FILE).gch