# A useful Makefile

# SRC is set to all the .cpp files in the current directory

SRC = $(wildcard *.cpp)

# The OBJ macro is built from the SRC macro

OBJ = $(SRC:.cpp=.o)

# Macros for the compiler, linker, and compiler options

GCC = g++
LINK = g++

CFLAGS = -Wall -std=c++11 -Wno-unused-variable -Wno-return-type -Wno-sign-compare -Wno-reorder
CXXFLAGS = $(CFLAGS)

# OpenGL/Mesa libraries for Linux
GL_LIBS = -lglut -lGLU -lGL -lm


# A macro to describe the main target

TARGET = vectorpaint

all: $(TARGET)
 
# The 'main' target depends on the files in the OBJ macro
# $^ is a make macro that contains the target dependencies
# $@ is a make macro that contains the target

$(TARGET): $(OBJ)
	$(LINK) -o $@ $^ $(GL_LIBS)

# Add a clean target to allow rebuilds

clean:
	rm -rf $(TARGET) *.o *.d

# This uses the compiler to create include file dependencies

-include $(SRC:.cpp=.d)

%.d: %.cpp
	@set -e; rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@
