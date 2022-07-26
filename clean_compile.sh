# this uses texlive (if you don't have texlive: sudo apt install texlive-full)

cd src/;
count=0;
declare -a folder_list;

for dir in *; do
    if [  -d "$dir" ]; then
        folder_list[$count]="$dir";
        ((count++));
    fi
done

cd ../;

rm -r output
for item in ${folder_list[*]}; do
    mkdir -p "./output/$item";
done

cp -f src/bib/referencias.bib output/bib/referencias.bib;

source compile.sh;

cd output/;
bibtex main_tcc_ufu.aux;
cd ../;

source compile.sh;
source compile.sh;