CC=/usr/bin/gcc
#CC=cl
CFLAGS=-I. -I.. -w
LDFLAGS=-L/usr/X11R6/lib
LDLIBS=-lGL -lGLU -lglut -lX11 -lXi -lXmu -lXext -ldl -lm
#LDLIBS=opengl32.lib glut32.lib glu32.lib
#TARGET=..\campus.exe
TARGET=../campus
#OBJS=main.obj keyboard.obj campus.obj camera.obj bezier.obj w32dirent.obj
OBJS=main.o keyboard.o campus.o camera.o bezier.o 

all: $(TARGET)
run: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	@del $(OBJS) $(TARGET) $(BUILDINGS) 

main.o keyboard.o: keyboard.h
main.o camera.o: camera.h
campus.o: ../buildings/building.h
camera.o bezier.o: bezier.h
