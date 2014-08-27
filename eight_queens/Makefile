
CC=/usr/bin/gcc
RM=/bin/rm
CFLAGS=-w
LDFLAGS=-L/usr/X11R6/lib
LDLIBS=-lGL -lGLU -lglut -lX11 -lXmu -lXi -lXext -lm
OBJS=board.o eight_queens.o queen.o solve.o
TARGET=eight_queens

all: $(TARGET) 
run: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	@$(RM) $(OBJS) $(TARGET)


