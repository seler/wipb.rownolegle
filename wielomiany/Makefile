SOURCES=szeregowy.c functions.c tests.c
OBJECTS=$(SOURCES:.c=.o)

all: szeregowy tests

szeregowy: szeregowy.o functions.o
	gcc $^ -o $@

tests: tests.o functions.o
	gcc $^ -o $@

.c.o:
	gcc -c $^ -o $@
