CC=/usr/bin/gcc
#CC=cl
CFLAGS=-I. -w
LDLIBS=-lm -lX11 -lGL -lGLU -lglut -lXi -lXmu -lXext
#LDLIBS=opengl32.lib glut32.lib glu32.lib
TARGET=solar
OBJS=main.o moon.o planet.o sun.o

all: $(TARGET)
run: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	@rm $(OBJS) $(TARGET)

main.o: color.h moon.h planet.h sun.h
moon.o: color.h moon.h
planet.o: color.h moon.h planet.h
sun.o: color.h moon.h planet.h sun.h

