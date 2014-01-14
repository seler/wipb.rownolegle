SOURCES=szeregowy.c functions.c tests.c
OBJECTS=$(SOURCES:.c=.o)

all: szeregowy rownolegly

szeregowy: szeregowy.o
	gcc -O2 $^ -o $@

rownolegly: rownolegly.o
	gcc -O2 -fopenmp $^ -o $@

#.c.o:
#	gcc -Wall -O2 -c $^ -o $@
szeregowy.o: szeregowy.c
	gcc -O2 -c $^ -o $@

rownolegly.o: rownolegly.c
	gcc -O2 -fopenmp -c $^ -o $@

clean:
	rm szeregowy rownolegly szeregowy.o rownolegly.o
