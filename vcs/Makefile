L0_TEX = lecture-0.tex
L0_PDF = lecture-0.pdf

PDF = \
	$(L0_PDF)

all: $(PDF)

$(L0_PDF): $(L0_TEX)
	pdflatex -shell-escape $^

clean:
	-rm $(PDF) 
.PHONY: clean
