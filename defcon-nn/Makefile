L0_TEX = 0x01.tex
L0_PDF = 0x01.pdf

PDF = \
	$(L0_PDF)

all: $(PDF)

$(L0_PDF): $(L0_TEX)
	pdflatex -shell-escape $^

$(L1_PDF): $(L1_TEX)
	pdflatex -shell-escape $^

clean:
	-rm $(PDF) 
.PHONY: clean
