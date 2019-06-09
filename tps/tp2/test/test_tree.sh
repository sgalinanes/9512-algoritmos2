#!/bin/bash -v


# Entrada vacia
touch entrada1.txt
./tp2 -i entrada1.txt -o salida1.txt -m tree
cat salida1.txt

echo -e "\n"

# Entrada thisisthe
cat entrada2.txt
./tp2 < entrada2.txt -m tree
./tp2 -p compress < entrada2.txt -o salida2.txt -m tree
./tp2 -p decompress < salida2.txt

echo -e "\n"

# Compresion, decompresion y diferencia entre archivos
cat entrada3.txt
./tp2 < entrada3.txt -m tree
./tp2 -p compress < entrada3.txt -o salida3.txt -m tree
./tp2 -p decompress < salida3.txt -o vuelta3.txt
diff -s entrada3.txt vuelta3.txt

echo -e "\n"

# Compresión, decompresión y diferencia en un archivo grande, 
# usando metodo tree
stat -c %s entrada9
./tp2 -i entrada9 -o salida9 -p compress -m tree
./tp2 -i salida9 -o vuelta9 -p decompress 
diff -s entrada9 vuelta9

#echo -e "\n"

# Decompresión de archivo con formato incorrecto
cat salida5.txt
./tp2 -i salida5.txt -o vuelta5.txt -p decompress

echo -e "\n"

# Descompresion de archivo con formato correcto, pero con índices fuera de rango
cat salida8
./tp2 -i salida8 -o vuelta8 -p decompress -m tree

echo -e "\n"

# Compresion y decompresión de un archivo 'docx' y 'pdf'
./tp2 -i entrada6.docx -o salida6.docx -p compress -m tree
./tp2 -i salida6.docx -o vuelta6.docx -p decompress
diff -s entrada6.docx vuelta6.docx

./tp2 -i entrada7.pdf -o salida7.pdf -m tree
./tp2 -i salida7.pdf -o vuelta7.pdf -p decompress
diff -s entrada7.pdf vuelta7.pdf

# Corremos nuevamente todas las pruebas con los param. largos

# Entrada vacia
touch entrada1.txt
./tp2 --input entrada1.txt --output salida1.txt --method tree
cat salida1.txt

echo -e "\n"

# Entrada thisisthe
cat entrada2.txt
./tp2 < entrada2.txt --method tree
./tp2 --process compress < entrada2.txt --output salida2.txt --method tree
./tp2 --process decompress < salida2.txt

echo -e "\n"

# Compresion, decompresion y diferencia entre archivos
cat entrada3.txt
./tp2 < entrada3.txt --method tree
./tp2 --process compress < entrada3.txt --output salida3.txt --method tree
./tp2 --process decompress < salida3.txt --output vuelta3.txt
diff -s entrada3.txt vuelta3.txt

echo -e "\n"

# Compresión, decompresión y diferencia en un archivo grande.
# usando metodo tree
stat -c %s entrada9
./tp2 --input entrada9 --output salida9 --process compress --method tree
./tp2 --input salida9 --output vuelta9 --process decompress
diff -s entrada4.txt vuelta4.txt

#echo -e "\n"

# Decompresión de archivo con formato incorrecto
cat salida5.txt
./tp2 --input salida5.txt --output vuelta5.txt --process decompress

echo -e "\n"

# Descompresion de archivo con formato correcto, pero con índices fuera de rango
cat salida8
./tp2 --input salida8 --output vuelta8 --process decompress --method tree

echo -e "\n"

# Compresion y decompresión de un archivo 'docx' y 'pdf'
./tp2 --input entrada6.docx --output salida6.docx --process compress --method tree
./tp2 --input salida6.docx --output vuelta6.docx --process decompress
diff -s entrada6.docx vuelta6.docx

./tp2 --input entrada7.pdf --output salida7.pdf --method tree
./tp2 --input salida7.pdf --output vuelta7.pdf --process decompress
diff -s entrada7.pdf vuelta7.pdf
