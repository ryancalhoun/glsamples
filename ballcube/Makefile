
CC=/usr/bin/gcc
RM=/bin/rm
CFLAGS=-w
LDFLAGS=-L/usr/X11R6/lib
LDLIBS=-lGL -lGLU -lglut -lX11 -lXmu -lXi -lXext -lm
OBJS=collide.o main.o point.o vec.o
TARGET=ballcube

all: $(TARGET) 
run: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	@$(RM) $(OBJS) $(TARGET)

main.c collide.c: ball.h point.h vec.h wall.h
