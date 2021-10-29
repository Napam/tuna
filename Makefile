CPPC = g++-11 -std=c++20 -Ofast
OUT_FILE = testapp.out
COMPILER_FLAGS = -o $(OUT_FILE)
MAIN_FILE = main.cpp
LINKS = -lSDL2 -lSDL2_ttf -lSDL2_gfx

HEADERS = -Iinclude

SOURCES = $(wildcard states/*.cpp) \
		  $(wildcard classes/*.cpp) \
		  $(wildcard utils/*.cpp)

testapp:
	$(CPPC) $(COMPILER_FLAGS) $(MAIN_FILE) $(SOURCES) $(HEADERS) $(LINKS)

mock:
	$(CPPC) -o mock.out mock.cpp $(SOURCES) $(HEADERS) $(LINKS)

clean:
	rm $(OUT_FILE)
	rm mock.out

