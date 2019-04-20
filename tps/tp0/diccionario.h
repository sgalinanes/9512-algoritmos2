#ifndef DICCIONARIO__H
#define DICCIONARIO__H

#include <iostream>
#include "types.h"

#define MAX_DICT 65535
#define MAX_ASCII 256

#define VOID 70000

using namespace std;

class Simbolo
{
	// Prefijo es un numero entero positivo. El vacío se representa con un valor fuera del rango del diccionario
	size_t prefijo;

	// Sufijo es un unsigned char, de esa manera representamos 0-255 (toda la tabla ASCII).
	unsigned char sufijo;

public:

	// ## --- Constructores --- ## //
	Simbolo();
	Simbolo(size_t, unsigned char);
	// ## --- Metodos --- ## //

	// Getters
	size_t getPrefijo();
	unsigned char getSufijo();

	// Setters
	void setSufijo(unsigned char);
	void setPrefijo(size_t);

	// Metodo de impresion
	void imprimir();

	// Overload: Comparacion
	bool operator==(const Simbolo &);
};

class Diccionario
{
	// Arreglo de simbolos (el diccionario)
	Simbolo sim[MAX_DICT];

	// Largo del diccionario
	size_t len;

	// Indice del primer elemento vacio en el diccionario
	size_t indice;

public:
	// ## --- Constructores --- ## //
	Diccionario();

	// ## --- Metodos --- ## //
	size_t getIndice();

	bool buscarSimbolo(const Simbolo &, size_t &);
	// TODO: status_t
	void agregarSimbolo(const Simbolo &);
	void imprimir();
	void resetDict();
	unsigned char getSufijoByIndex(size_t);
	//TODO: una sola funcipon checkIndex con parametro bool default false para chequear ascii
	bool checkIndexInASCII(size_t );
	bool checkIndex(size_t );
	/*
	status_t imprimirSimbolos(size_t, size_t, Simbolo &, ostream *);
	status_t imprimirSimbolos(size_t , ostream *);
	status_t imprimirPrefijo(size_t, ostream *);
	*/
	status_t reconstruirCadena(size_t , Simbolo &, ostream *, size_t );

};

#endif