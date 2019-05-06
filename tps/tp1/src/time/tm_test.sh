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

# ./tp1 -o salida -m tree
# rm *.txt

# Observamos los resultados obtenidos para los métodos
cat resultados_normal.csv
cat resultados_list.csv
# cat resultados_tree.csv