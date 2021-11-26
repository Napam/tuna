CXX = g++-11
CXXFLAGS = -std=c++20 -Ofast -Winvalid-pch
OUT_FILE = simpleapp.out
MAIN_FILE = main.cpp
PCH_FILE = include/tunapch.hpp
LINKS = -lSDL2 -lSDL2_ttf -lSDL2_gfx -ldl
VENDOR_DIR = vendor
export BUILD_DIR = build

INCLUDES = -Iinclude \
		   -I$(VENDOR_DIR_DIR)/Glad/include \
		   -I$(VENDOR_DIR)/json/single_include \
		   -I$(VENDOR_DIR)/glm

MAKEFLAGS += -j$(shell nproc --all)

SOURCES = $(wildcard states/*.cpp) \
		  $(wildcard classes/*.cpp) \
		  $(wildcard utils/*.cpp)

OBJECTS = $(BUILD_DIR)/$(MAIN_FILE:.cpp=.o) \
		  $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o))) \
		  $(VENDOR_DIR)/Glad/$(BUILD_DIR)/glad.o

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
	mkdir $(BUILD_DIR)
	$(MAKE) -C $(VENDOR_DIR)/Glad

.PHONY: clean clean-all

clean-all: clean
	$(MAKE) -C $(VENDOR_DIR)/Glad clean

clean:
	rm -rf $(OUT_FILE) \
		  $(BUILD_DIR) \
		  $(PCH_FILE).gch
