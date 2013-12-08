CC=gcc
CFLAGS=-fopenmp -lm
LINT=cppcheck --enable=all $<;
IMGS:=$(patsubst %.png,%.eps,$(wildcard *.png))
RESULT=pi

all: $(RESULT) $(RESULT).pdf

$(RESULT): main.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(LINT) $(CC) $(CFLAGS) -c $< -o $@

$(RESULT).pdf: main.ps
	ps2pdf $^

main.ps: main.dvi
	dvips $^

main.dvi: main.tex $(IMGS) 
	latex -shell-escape $^

%.eps : %.png
	convert $< $@

clean:
	rm -rf $(RESULT) *.o *.dvi *.ps *.pdf *.eps *.aux 
