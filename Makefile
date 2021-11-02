CPPC = g++-11 
OUT_FILE = simpleapp.out
COMPILER_FLAGS = -std=c++20 -Ofast -Winvalid-pch
MAIN_FILE = main.cpp
LINKS = -lSDL2 -lSDL2_ttf -lSDL2_gfx

HEADERS = -Iinclude

SOURCES = $(wildcard states/*.cpp) \
		  $(wildcard classes/*.cpp) \
		  $(wildcard utils/*.cpp)

simpleapp:
	$(CPPC) $(COMPILER_FLAGS) -o $(OUT_FILE) $(MAIN_FILE) $(SOURCES) $(HEADERS) $(LINKS)

pch:
	$(CPPC) $(COMPILER_FLAGS) include/tunapch.h 

mock:
	$(CPPC) -o mock.out mock.cpp $(SOURCES) $(HEADERS) $(LINKS)

glm:
	$(CPPC) $(COMPILER_FLAGS) -o glm.out testglm.cpp $(HEADERS) $(LINKS)

clean:
	rm $(OUT_FILE)
	rm mock.out
	rm glm.out
