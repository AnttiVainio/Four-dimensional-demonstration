PROJECT = 4D_linux
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
CFLAGS  = -c -O2 -Wall -pedantic
LIBRARIES = `sdl-config --cflags --libs` -lGL -lGLU

all: $(PROJECT)

%.o: %.cpp
	g++ $(CFLAGS) $< -o $@

$(PROJECT): $(OBJECTS)
	g++ -s $(OBJECTS) -o $(PROJECT) $(LIBRARIES)

clean:
	rm $(OBJECTS) -f

