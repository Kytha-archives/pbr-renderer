CC=g++
TARGETDIR=bin
BUILDDIR=bin-int
SRCDIR=src
INCLUDE=-Iinclude/glad
LIBS=
SOURCES:=src/glad.cpp
DEFINES=

OBJECTS := $(patsubst $(SRCDIR)%,$(BUILDDIR)%,$(SOURCES:.cpp=.o))
TARGET= bin/libglad.a 

#Link
$(TARGET): $(OBJECTS)
	$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	ar -cvq $(TARGET)  $^


#Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) $(DEFINES)
