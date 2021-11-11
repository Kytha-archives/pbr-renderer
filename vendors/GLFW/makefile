CC=gcc
TARGETDIR=bin
BUILDDIR=bin-int
SRCDIR=src
INCLUDE=-Iinclude/GLFW
LIBS=
SOURCES:=src/context.c src/init.c src/input.c src/monitor.c src/vulkan.c src/window.c src/platform.c src/null_init.c src/null_joystick.c src/null_monitor.c src/null_window.c
DEFINES=

ifeq ($(OS),Windows_NT)
	SOURCES+= src/win32_init.c src/win32_joystick.c src/win32_monitor.c src/win32_time.c src/win32_thread.c src/win32_window.c src/wgl_context.c src/egl_context.c src/osmesa_context.c src/win32_module.c
	DEFINES=-D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS 
else
	SOURCES+= src/x11_init.c src/x11_monitor.c src/x11_window.c src/xkb_unicode.c src/posix_time.c src/posix_module.c src/posix_thread.c src/glx_context.c src/egl_context.c src/osmesa_context.c src/linux_joystick.c
	DEFINES=-D_GLFW_X11
endif
$(info $(SOURCES))

OBJECTS := $(patsubst $(SRCDIR)%,$(BUILDDIR)%,$(SOURCES:.c=.o))
TARGET= libglfw3.a

#run target to compile and build, and then launch the executable  

#Link
$(TARGET): $(OBJECTS)
	ar -cvq $(TARGETDIR)/$(TARGET)  $^


#Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) $(DEFINES)