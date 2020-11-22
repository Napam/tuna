CPPC = g++
OUT_FILE = boids.out
COMPILER_FLAGS = -o $(OUT_FILE)

HEADERS = headers/utils.hpp \
		  headers/base_state.hpp

SOURCES = main.cpp \
		  utils/utils.cpp \
		  states/base_state.cpp

all:
	$(CPPC) $(COMPILER_FLAGS) $(SOURCES) $(HEADERS) -lSDL2

clean:
	rm $(OUT_FILE)