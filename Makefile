CPPC = g++-10 -std=c++20 -O3
OUT_FILE = boids.out
COMPILER_FLAGS = -o $(OUT_FILE)
MAIN_FILE = main.cpp
LINKS = -lSDL2 -lSDL2_ttf -lSDL2_gfx

HEADERS = $(wildcard include/.hpp)

SOURCES = $(wildcard states/*.cpp) \
		  $(wildcard classes/*.cpp) \
		  $(wildcard utils/*.cpp)

all:
	$(CPPC) $(COMPILER_FLAGS) $(MAIN_FILE) $(SOURCES) $(HEADERS) $(LINKS)

mock:
	$(CPPC) -o mock.out mock.cpp $(SOURCES) $(HEADERS) $(LINKS)

clean:
	rm $(OUT_FILE)
	rm mock.out
