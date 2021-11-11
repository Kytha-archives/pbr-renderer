CC=g++
TARGETDIR=bin
BUILDDIR=bin-int
SRCDIR=src
INCLUDE=
LIBS=
SOURCES:=src/imgui_tables.cpp src/imgui_widgets.cpp src/imgui_draw.cpp src/imgui.cpp
DEFINES=

OBJECTS := $(patsubst $(SRCDIR)%,$(BUILDDIR)%,$(SOURCES:.cpp=.o))
TARGET= bin/libimgui.a 

#Link
$(TARGET): $(OBJECTS)
	$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	ar -cvq $(TARGET)  $^


#Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) $(DEFINES)
