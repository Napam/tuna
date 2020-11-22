CPPC = g++
OUT_FILE = boids.out
COMPILER_FLAGS = -o $(OUT_FILE)

HEADERS = include/utils.hpp \
		  include/base_state.hpp \
		  include/boids_state.hpp \

SOURCES = main.cpp \
		  utils/utils.cpp \
		  states/base_state.cpp \
		  states/boids_state.cpp \

all:
	$(CPPC) $(COMPILER_FLAGS) $(SOURCES) $(HEADERS) -lSDL2

clean:
	rm $(OUT_FILE)