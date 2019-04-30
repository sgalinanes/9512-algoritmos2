#include <iostream>
#include "diccionario.h"
#include "types.h"
#include "arreglo.h"

using namespace std;

// CLASE SIMBOLO //
// ## --- Constructores --- ## //
Simbolo::Simbolo()
{
	// Inicializar el prefijo a vacio y el sufijo (por def.) al caracter nulo
	prefijo = VOID;
	sufijo = 0;
	primero = VOID;
	siguiente = VOID;
	derecha = VOID;
	izquierda = VOID;
}

Simbolo::Simbolo(unsigned short prefijo, unsigned char sufijo, unsigned short primero=VOID, unsigned short siguiente=VOID, unsigned short derecha=VOID, unsigned short izquierda=VOID)
{
	this->prefijo = prefijo;
	this->sufijo = sufijo;	
	this->primero = primero;
	this->siguiente = siguiente;
	this->derecha = derecha;
	this->izquierda = izquierda;
}

// ## --- Metodos --- ## //

// Getters
unsigned short Simbolo::getPrefijo()
{
	return prefijo;
}

unsigned char Simbolo::getSufijo()
{
	return sufijo;
}

// Setters
void Simbolo::setSufijo(unsigned char sufijo)
{
	this->sufijo = sufijo;
}

void Simbolo::setPrefijo(unsigned short prefijo)
{
	this->prefijo = prefijo;
}

// Metodo de impresion
void Simbolo::imprimir()
{
	cout << "Prefijo: " << prefijo << endl;
	cout << "Sufijo: " << (int)sufijo << "/" << sufijo  << endl;
}

// Overload: Comparacion
bool Simbolo::operator==(const Simbolo &sim)
{
	// Comparamos el simbolo componente por componente
	if(prefijo == sim.prefijo && sufijo == sim.sufijo)
		return true;

	return false;
}

// CLASE DICCIONARIO //
// ## --- Constructores --- ## //
Diccionario::Diccionario():sim(MAX_DICT)
{
	for(size_t i = 0; i < MAX_ASCII; i++)
		// En los primeros 256 lugares, copia los simbolos ASCII correspondientes.
		sim[i].setSufijo(i);

	len = MAX_DICT;
	indice = MAX_ASCII;
}

// ## --- Metodos --- ## //
unsigned short Diccionario::getIndice()
{
	return this->indice;
}

bool Diccionario::buscarSimbolo(const Simbolo &simbolo, unsigned short &idx)
{
	// Recibe por parametro el simbolo, devuelve el indice en el diccionario
	// en el que se encuentra un simbolo que es igual al pasado por parametro

	int a = 0;
	
	/* 	a = 0 => busqueda secuencial
		a = 1 => busqueda lista
		a = 2 => busqueda abb
	*/

	if(a == 0)
	{
		for(idx = 0; idx < len; idx++)
		{
			if(sim[idx] == simbolo)
				return true;
		}		
	}
	else if(a == 1)
	{
		/*

		unsigned short idx_pref = sim[simbolo.getPrefijo()].getPrimer();
		if(sim[idx_pref] == simbolo)
		{
			return ok
		}
		else
		{
			idx_pref = idx_pref->sig;
			continue;
		}

		*/
	}
	else
	{
		/*

			//ABB

		*/
	}


	return false;
}

void Diccionario::agregarSimbolo(const Simbolo &simbolo)
{
	// Recibe por parametro el simbolo, lo agrega al diccionario y actualiza el indice.
	// En caso de que el indice agregado sea el ultimo disponible, resetea el diccionario.
	// (No agrega el último pues lo borraría)

	if(indice < len-1)
	{
		sim[indice] = simbolo;
		indice++;		
	}
	else
		resetDict();
}

void Diccionario::resetDict()
{
	// Resetea el diccionario dejando unicamente los simbolos correspondientes a los ASCII, es
	// decir los indices entre 0 y 255. Resetea el arreglo de simbolos y el indice.

	for(size_t i = MAX_ASCII; i < len; i++)
	{
		sim[i].setPrefijo(VOID);
		sim[i].setSufijo(0);
	}

	indice = MAX_ASCII;
}

void Diccionario::imprimir()
{
	// Imprime los simbolos contenidos en el diccionario

	for(size_t i = MAX_ASCII; i < indice; i++)
	{
		cout << "Indice " << i << " ";
		sim[i].imprimir();
	}
}

status_t Diccionario::getSufijoByIndex(unsigned short indice, unsigned char &suf)
{
	// Devuelve un status_t en caso de que el indice pasado por parametro sea mayor al largo del arreglo.
	// Modifica el sufijo del indice del diccionario pasado por parametro como referencia.

	if(indice > len)
	{
		return ERROR_INDEX_OUT_OF_RANGE;
	}

	suf = sim[indice].getSufijo();
	return OK;
}


bool Diccionario::checkIndex(unsigned short indice, bool ASCII=false)
{
	// Chequea si el indice esta en el diccionario.
	// En caso de que el parametro ASCII sea true, entonces unicamente chequea en la parte del diccionario donde el prefijo es nulo. 
	// (los ascii)

	unsigned short comp = ASCII ? MAX_ASCII : this->indice;

	if(indice >= comp)
		return false;

	return true;
}

status_t Diccionario::reconstruirCadena(unsigned short indice_act, Simbolo &buffer, ostream *oss, unsigned short indice_ant = VOID)
{
	status_t st;

	// Chequeamos si el indice esta en el diccionario
	if(!checkIndex(indice_act))
	{
		// Si el indice anterior es igual al indice actual entonces tenemos un error: Ni el indice anterior ni el actual
		// pertenecen al diccionario, entonces no podemos realizar la reconstruccion (la data es erronea).
		if(indice_ant == indice_act)
		{
			return ERROR_READ_FILE;	
		}

		// Llamamos nuevamente a la función pero dandole el indice anterior como indice actual (el prefijo del simbolo a crear)
		if( (st = reconstruirCadena(indice_ant, buffer, oss, indice_ant)) != OK)
			return st;

		// Imprimimos el sufijo del buffer (que sera el primer caracter de la cadena del indice anterior previamente pasado)
		*oss << buffer.getSufijo();

		return OK;

	}
	else
	{
		// Creamos variables para el prefijo y sufijo del indice al que accedemos.
		unsigned short prefijo_idx = sim[indice_act].getPrefijo();
		unsigned char sufijo_idx = sim[indice_act].getSufijo();

		// Cond.de corte: Que el prefijo sea void, es decir que llegamos al simbolo que esta en el diccionario ASCII
		if(prefijo_idx == VOID)
		{
			// Seteamos el sufijo del buffer al primer caracter que se imprimirá. (Es el que guardamos en el simbolo que agregamos al diccionario)	
			buffer.setSufijo(sufijo_idx);

			// Imprimimos el primer caracter al reconstruir la cadena.
			*oss << sufijo_idx;
			return OK;
		}

		// Llamamos nuevamente a la función, sin especificar el parametro indice_ant (no hace falta usarlo), pasando el prefijo del indice
		// como nuevo indice actual de la llamada posterior, de esta manera, obtendremos luego el prefijo del prefijo del indice, hasta que
		// este sea el nulo, en cuyo caso agregamos el sufijo al buffer, imprimimos y retornamos.
		reconstruirCadena(prefijo_idx, buffer, oss);

		// Imprimimos el sufijo del indice.
		*oss << sufijo_idx;

		return OK;
	}		
}