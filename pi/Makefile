SOURCES=main.tex
RESULT=rafal_selewonko_praca_dyplomowa
IMGS:=$(patsubst %.png,%.eps,$(wildcard *.png))
DIR=build

all: $(SOURCES) $(RESULT)

$(RESULT): $(SOURCES)
	mkdir -p $(DIR); latexmk -jobname=$(DIR)/$@ -pdf $^

%.eps : %.png
	convert $< $@

clean:
	rm -rf $(DIR)


