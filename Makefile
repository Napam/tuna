CPPC = g++
OUT_FILE = boids.out
COMPILER_FLAGS = -o $(OUT_FILE)

HEADERS = headers/manager.hpp \
		  headers/utils.hpp \

SOURCES = main.cpp \
		  states/manager.cpp \
		  utils/utils.cpp

all:
	$(CPPC) $(COMPILER_FLAGS) $(SOURCES) $(HEADERS) -lSDL2

clean:
	rm $(OUT_FILE)