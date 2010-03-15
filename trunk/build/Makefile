ROOT_DIR := ..
BIN_DIR := $(ROOT_DIR)/bin
SRC_DIR := $(ROOT_DIR)/src

VPATH = $(SRC_DIR)

CC := colorgcc
EXT := cpp
COMMON_CCFLAGS := -g -c -Wall

MAIN_EXE := $(BIN_DIR)/zoobabiesd

.PHONY: all
all: $(MAIN_EXE)

CCFLAGS := $(COMMON_CCFLAGS) -I/usr/X11R6/include/ -I/usr/include/lua5.1
LIBS := -L/usr/X11R6/lib64/ -L/lua-5.1/lib/ -L/usr/lib/ -L/usr/local/lib/ -llua5.1 -lluabind -lGL -lGLU -lX11 -lXmu -lXi -lm -lSDL -lSDL_mixer -lfreeimage -lode

SRC_FILES := $(wildcard $(SRC_DIR)/*.$(EXT))
OBJECT_FILES := $(notdir $(SRC_FILES:.$(EXT)=.o))
DEPENDENCY_FILES := $(notdir $(SRC_FILES:.$(EXT)=.d))

#build the main exe
$(MAIN_EXE): $(OBJECT_FILES)
	@$(CC) $(OBJECT_FILES) -o $(MAIN_EXE) $(LIBS)
	@echo Linking $(notdir $(MAIN_EXE))


#Create a .d file for each .c source file. The .d file contains a make rule with the dependencies for the .c file.
$(DEPENDENCY_FILES): %.d: %.$(EXT)
	@$(CC) -MM $< > $@
	@echo Generating deps for $(notdir $<)

#Compile the .o file for each .c file using the make rules in the .d files.
-include $(DEPENDENCY_FILES)

#Implicit rules to make sure our libraries are included and the desired gcc flags are used when compiling our objects.
$(OBJECT_FILES): %.o: %.cpp
	@$(CC) $(CCFLAGS) $(LIBS) $< -o $@
	@echo Compiling $(notdir $<)

.PHONY: clean	
clean:
	rm -f *.o *.d $(MAIN_EXE)
