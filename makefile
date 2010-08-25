CC = g++ -lGL -lGLU -lX11
CFLAGS = -Wall
PROG = 4th_Assignment

SRCS = CS161_Assignment4.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
