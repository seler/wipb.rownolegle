CC=mpic++
CFLAGS=-g
CPPLINT=python cpplint.py --linelength=120 $<;

all: pingpong pingpong.pdf

pingpong: main.o
	$(CC) $(LFLAGS) $^ -o $@

main.o: main.cpp
	$(CPPLINT) $(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *o pingpong

