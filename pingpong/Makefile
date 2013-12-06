CC=mpic++
CFLAGS=-g
CPPLINT=python cpplint.py --linelength=120 $<;
IMGS:=$(patsubst %.png,%.eps,$(wildcard *.png))

all: pingpong pingpong.pdf

pingpong: main.o
	$(CC) $(LFLAGS) $^ -o $@

main.o: main.cpp
	$(CPPLINT) $(CC) $(CFLAGS) -c $< -o $@

pingpong.pdf: pingpong.ps
	ps2pdf $^

pingpong.ps: pingpong.dvi
	dvips $^

pingpong.dvi: pingpong.tex $(IMGS) 
	latex -shell-escape $^

%.eps : %.png
	convert $< $@

clean:
	rm -rf *o pingpong pingpong.dvi pingpong.ps pingpong.pdf *.eps

