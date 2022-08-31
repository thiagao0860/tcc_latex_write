# this uses texlive (if you don't have texlive: sudo apt install texlive-full)

cd src/;
pdflatex -output-directory '../output' main_tcc_ufu.tex;
cd ../;
cp -f ./output/main_tcc_ufu.pdf ./main_tcc_ufu.pdf
