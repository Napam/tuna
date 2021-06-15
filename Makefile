CPPC = g++ 
OUT_FILE = boids.out
COMPILER_FLAGS = -o $(OUT_FILE)
MAIN_FILE = main.cpp
LINKS = -lSDL2 -lSDL2_ttf -lSDL2_gfx

HEADERS = include/utils.hpp \
		  include/fonts.hpp \
		  include/base_state.hpp \
		  include/boids_state.hpp \

SOURCES = utils/utils.cpp \
		  classes/fonts.cpp \
		  states/base_state.cpp \
		  states/boids_state.cpp \

all:
	$(CPPC) $(COMPILER_FLAGS) $(MAIN_FILE) $(SOURCES) $(HEADERS) $(LINKS)

mock:
	$(CPPC) -o mock.out mock.cpp $(SOURCES) $(HEADERS) $(LINKS)

clean:
	rm $(OUT_FILE)
