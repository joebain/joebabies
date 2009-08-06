CC = g++
CFLAGS = -c -Wall -g
INCLUDE = -I/usr/X11R6/include/ -I/usr/include/lua5.1 -I/usr/local/include/luabind

LDFLAGS = -L/usr/X11R6/lib64/ -L/lua-5.1/lib/ -L/usr/lib/ -L/usr/local/lib/
LDLIBS_R = -Wl,-Bstatic -llua5.1 -lluabind -Wl,-Bdynamic -lGL -lGLU -lX11 -lXmu -lXi -lm -lSDL -lSDL_mixer
LDLIBS_D = -llua5.1 -lluabindd -lGL -lGLU -lX11 -lXmu -lXi -lm -lSDL -lSDL_mixer
SOURCES = src/Block.cpp src/Display.cpp src/Face.cpp src/Main.cpp src/ModelLoader.cpp src/Obj.cpp src/Texture.cpp src/Vector2f.cpp src/Vector2i.cpp src/Vector3f.cpp src/Vector3i.cpp src/Vertex.cpp src/World.cpp src/Controller.cpp src/Camera.cpp src/Block3D.cpp src/Block2D.cpp src/Floor.cpp src/Timer.cpp src/Sky.cpp src/Block2DText.cpp src/BlockFactory.cpp src/LuaBinder.cpp src/Buttons.cpp src/AudioMixer.cpp src/AudioFile.cpp src/Block3DImaginary.cpp src/Block3DFlat.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = zoobabiesd
EXECUTABLE_R = zoobabies

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LDLIBS_D) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

release: $(SOURCES) $(EXECUTABLE_R)

$(EXECUTABLE_R): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LDLIBS_R) $(OBJECTS) -o $@

clean:
	rm -f src/*.o $(EXECUTABLE)
	
clean-release:
	rm -f src/*.o $(EXECUTABLE_R)
