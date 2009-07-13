CC = g++
CFLAGS = -c -Wall
INCLUDE = -I/usr/X11R6/include/ -I/usr/include/lua5.1
LDFLAGS = -L/usr/X11R6/lib64/ -Llua-5.1/lib/
LDLIBS =  -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm -llua5.1
SOURCES = src/Block.cpp src/Display.cpp src/Face.cpp src/Main.cpp src/ModelLoader.cpp src/Obj.cpp src/Texture.cpp src/Vector2f.cpp src/Vector2i.cpp src/Vector3f.cpp src/Vector3i.cpp src/Vertex.cpp src/World.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = babies

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm src/*.o $(EXECUTABLE)
