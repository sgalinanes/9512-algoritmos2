#!/bin/bash -v

# Eliminamos viejos archivos y creamos output
rm *.csv
rm salida
touch salida

# Comparamos los distintos metodos
./tm_tp1 -o salida -m normal
rm *.txt

./tm_tp1 -o salida -m list
rm *.txt

./tm_tp1 -o salida -m tree
rm *.txt

# Observamos los resultados obtenidos para los métodos
cat resultados_normal.csv
cat resultados_list.csv
cat resultados_tree.csv

# Movemos los CSV a otro directorio temporalmente.
mkdir temp 
mv *.csv temp

# Eliminamos viejos archivos y creamos output
rm *.csv
rm salida
touch salida

# Comparamos ahora solo lista y arbol, utilizando mas pruebas con el programa
# que contiene más pruebas.

./tm_tp1_lt -o salida -m list
rm *.txt

./tm_tp1_lt -o salida -m tree 
rm *.txt

# Observamos los resultados obtenidos para los metodos
cat resultados_list.csv
cat resultados_tree.csv

# Cambiamos el nombre de los CSV para poder traer nuevevamente los anteriores
mv resultados_list.csv resultados_list2.csv
mv resultados_tree.csv resultados_tree2.csv 
mv temp/*.csv .
rmdir temp