#!/bin/bash -v


touch entrada1.txt
./tp0 -i entrada1.txt -o salida1.txt
cat salida1.txt

echo -e "\n"

cat entrada2.txt
./tp0 < entrada2.txt
./tp0 -p compress < entrada2.txt -o salida2.txt
./tp0 -p decompress < salida2.txt

echo -e "\n"

cat entrada3.txt
./tp0 < entrada3.txt
./tp0 -p compress < entrada3.txt -o salida3.txt
./tp0 -p decompress < salida3.txt -o vuelta3.txt
diff -s entrada3.txt vuelta3.txt

echo -e "\n"

stat -c %s entrada4.txt
./tp0 -i entrada4.txt -o salida4.txt -p compress
./tp0 -i salida4.txt -o vuelta4.txt -p decompress
diff -s entrada4.txt vuelta4.txt

#echo -e "\n"

cat salida5.txt
./tp0 -i salida5.txt -o vuelta5.txt -p decompress
