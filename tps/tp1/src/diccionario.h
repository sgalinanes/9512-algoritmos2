#ifndef DICCIONARIO__H
#define DICCIONARIO__H

#include <iostream>
#include "types.h"
#include "arreglo.h"

#define MAX_DICT 65535
#define MAX_ASCII 256

#define VOID 65535

#define OPT_NORMAL "normal"
#define OPT_LIST "list"
#define OPT_TREE "tree" 

using namespace std;

class Simbolo
{
	// Prefijo es un numero entero positivo. El vacío se representa con un valor fuera del rango del diccionario
	unsigned short prefijo;

	// Sufijo es un unsigned char, de esa manera representamos 0-255 (toda la tabla ASCII).
	unsigned char sufijo;

	// Primero es un entero positivo. Indicará el indice del primer prefijo que sea igual al indice del simbolo actual.
	unsigned short primero;

	/* Para busqueda lista */
	// Siguiente es un entero positivo. Indicará el indice del siguiente simbolo con igual prefijo que el simbolo actual.
	unsigned short siguiente;

	/* Para busqueda ABB */
	
	// Derecha es un entero positivo. Indicará el indice del siguiente simbolo con igual prefijo que el simbolo actual
	// y que además su sufijo sea "mayor"
	unsigned short derecha;

	// Izquierda es un entero positivo. Indicará el índice del siguiente simbolo con igual prefijo que el simbolo actual
	// y que ademas su sufijo sea "menor"
	unsigned short izquierda;

public:

	// ## --- Constructores --- ## //
	Simbolo();
	Simbolo(unsigned short, unsigned char, unsigned short, unsigned short, unsigned short, unsigned short);
	// ## --- Metodos --- ## //

	// Getters
	unsigned short getPrefijo() const;
	unsigned char getSufijo() const;
	unsigned short getPrimero() const;
	unsigned short getSig() const;
	unsigned short getDerecha() const;
	unsigned short getIzquierda() const;

	// Setters
	void setSufijo(unsigned char);
	void setPrefijo(unsigned short );
	void setPrimero(unsigned short );
	void setSig(unsigned short );
	void setDerecha(unsigned short );
	void setIzquierda(unsigned short );
	// Metodo de impresion
	void imprimir();

	// Overload: Comparacion
	bool operator==(const Simbolo &) const;
	bool operator>(const Simbolo &) const;
	bool operator<(const Simbolo &) const;

};

class Diccionario
{
	// Arreglo de simbolos (el diccionario)
	Arreglo<Simbolo> sim;

	// Largo del diccionario
	size_t len;

	// Indice del primer elemento vacio en el diccionario
	unsigned short indice;

public:
	// ## --- Constructores --- ## //
	Diccionario();

	// ## --- Metodos --- ## //
	unsigned short getIndice();

	bool buscarSimbolo(const Simbolo &, unsigned short &, string);
	bool busquedaNormal(const Simbolo &, unsigned short &);
	bool busquedaArbol(const Simbolo &, unsigned short &);
	bool busquedaLista(const Simbolo &, unsigned short &);
	void agregarSimbolo(Simbolo &, string );
	void imprimir();
	void resetDict();
	status_t getSufijoByIndex(unsigned short, unsigned char &);
	bool checkIndex(unsigned short, bool );
	status_t reconstruirCadena(unsigned short , Simbolo &, ostream *, unsigned short );

};

#endif
