SOURCES=szeregowy.c functions.c tests.c
OBJECTS=$(SOURCES:.c=.o)

all: szeregowy

szeregowy: szeregowy.o
	gcc -O2 $^ -o $@

.c.o:
	gcc -O2 -c $^ -o $@
