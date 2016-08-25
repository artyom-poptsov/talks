L0_TEX = lecture-0.tex
L0_PDF = lecture-0.pdf
L1_TEX = lecture-1.tex
L1_PDF = lecture-1.pdf

PDF = \
	$(L0_PDF)	\
	$(L1_PDF)

all: $(PDF)

$(L0_PDF): $(L0_TEX)
	pdflatex -shell-escape $^

$(L1_PDF): $(L1_TEX)
	pdflatex -shell-escape $^

clean:
	-rm $(PDF) 
.PHONY: clean
