#------------------------------------------------------------------------------
# primary source: .eps
# store ROOT plots in .eps format, make .png and .pdf out of .eps files
#------------------------------------------------------------------------------
dir=.

tex_files := $(wildcard *.tex)

pdfs := $(patsubst figures/eps/%.eps, figures/pdf/%.pdf,  $(wildcard figures/eps/*.eps ))

pngs := $(patsubst figures/eps/%.eps, figures/png/%.png, $(wildcard figures/eps/*.eps ))

figures/pdf/%.pdf: figures/eps/%.eps
	ps2pdf -dEPSCrop $? $@

figures/png/%.png: figures/eps/%.eps
	convert -density 400 -depth 8 -quality 85  $? $@

pdf: $(pdfs) 
# 	echo $?
png: $(pngs) 
# 	echo $?

note: $(tex_files) pdf 
	if [ ! -d tmp ] ; then mkdir tmp ; fi ; \
	pdflatex -output-directory=tmp $^ ; \
	cd tmp ; \
	bibtex mu2e_31019 ; \
	cd .. ; \
	pdflatex -output-directory=tmp $^

all: pdf note
	echo $(pdfs)
	echo $?
