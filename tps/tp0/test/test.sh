#!/bin/bash

echo "Caso de prueba 1"
echo  "$ touch entrada1.txt"
touch entrada1.txt
echo  "$ ./tp0 -i entrada1.txt -o salida1.txt"
./tp0 -i entrada1.txt -o salida1.txt
echo "$ cat salida1.txt"
cat salida1.txt
echo "$ "

echo -e "\n"

echo "Caso de prueba 2"
echo "$ cat entrada2.txt"
cat entrada2.txt
echo "$ ./tp0 < entrada2.txt"
./tp0 < entrada2.txt
echo "$ ./tp0 -p compress < entrada2.txt -o salida2.txt"
./tp0 -p compress < entrada2.txt -o salida2.txt
echo "$ ./tp0 -p decompress < salida2.txt"
./tp0 -p decompress < salida2.txt

echo -e "\n"

echo "Caso de prueba 3"
echo "$ cat entrada3.txt"
cat entrada3.txt
echo "$ ./tp0 < entrada3.txt"
./tp0 < entrada3.txt
echo "$ ./tp0 -p compress < entrada3.txt -o salida3.txt"
./tp0 -p compress < entrada3.txt -o salida3.txt
echo "$ ./tp0 p decompress < salida3.txt -o vuelta3.txt"
./tp0 -p decompress < salida3.txt -o vuelta3.txt
echo "$ diff -s entrada3.txt vuelta3.txt"
diff -s entrada3.txt vuelta3.txt

echo -e "\n"

echo "Caso de prueba 4"
echo "$ ./tp0 -i entrada4.txt -o salida4.txt -p compress"
./tp0 -i entrada4.txt -o salida4.txt -p compress
echo "$ ./tp0 -i salida4.txt -o vuelta4.txt -p decompress"
./tp0 -i salida4.txt -o vuelta4.txt -p decompress
echo "$ diff -s entrada4.txt vuelta4.txt"
diff -s entrada4.txt vuelta4.txt

echo -e "\n"
