make
cd Tbash
sh check_valid2.sh ../lem-in | grep -v "success"
sh check_valid.sh ../lem-in | grep -v "success"