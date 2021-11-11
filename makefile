LIBS= -lGLU -lGL -lgdi32 -lassimp
CFLAGS=-std=c++11
CC=g++
EXEEXT=
RM=rm
TARGETDIR=build
BUILDDIR=bin-int
ASSETDIR=assets
INCLUDE=-Ivendors/GLFW/include -Ivendors/glm/include
SRCDIR=src
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
ASSETS := $(wildcard $(ASSETDIR)/*)
$(info $(SOURCES))
OBJECTS := $(patsubst $(SRCDIR)%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
TARGET= main

$(info $(OBJECTS))

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe
	LIBS = vendors/GLFW/bin/libglfw3.a -lopengl32 -lgdi32 -lassimp
else
# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LIBS = -lassimp -framework Carbon -framework OpenGL -framework GLUT
	endif
endif

#run target to compile and build, and then launch the executable  

production: CFLAGS += -O3
production: all

debug: CFLAGS += -g -O0
debug: all  


directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)/$(ASSETDIR)


all: cleaner directories assets glfw $(TARGET)

link: $(TARGET)

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET)  $^ $(CFLAGS) $(LIBS)


#Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)


#Clean only Objecst
clean:
	-@$(RM) -r $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	-@$(RM) -r $(TARGETDIR)

$(TARGETDIR)/$(ASSETDIR)/%: $(ASSETDIR)/%
	mkdir -p $(@D)
	cp -r $< $@

glfw: 
	$(MAKE) -C vendors/GLFW

assets: $(patsubst $(ASSETDIR)/%,$(TARGETDIR)/$(ASSETDIR)/%,$(ASSETS))