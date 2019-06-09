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
unsigned short Simbolo::getPrefijo() const
{
	return prefijo;
}

unsigned char Simbolo::getSufijo() const
{
	return sufijo;
}

unsigned short Simbolo::getPrimero() const
{
	return primero;
}

unsigned short Simbolo::getSig() const
{
	return siguiente;
}

unsigned short Simbolo::getDerecha() const
{
	return derecha;
}

unsigned short Simbolo::getIzquierda() const
{
	return izquierda;
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

void Simbolo::setPrimero(unsigned short primero)
{
	this->primero = primero;
}

void Simbolo::setSig(unsigned short siguiente)
{
	this->siguiente = siguiente;
}

void Simbolo::setDerecha(unsigned short derecha)
{
	this->derecha = derecha;
}

void Simbolo::setIzquierda(unsigned short izquierda)
{
	this->izquierda = izquierda;
}

// Metodo de impresion
void Simbolo::imprimir()
{
	cout << "Prefijo: " << prefijo << endl;
	cout << "Sufijo: " << (int)sufijo << "/" << sufijo  << endl;
}

// Overload: Comparacion
bool Simbolo::operator==(const Simbolo &sim) const
{
	// Comparamos el simbolo componente por componente
	if(prefijo == sim.prefijo && sufijo == sim.sufijo)
		return true;

	return false;
}

// Overload: Comparacion
bool Simbolo::operator>(const Simbolo &sim) const
{
	// Comparamos el simbolo
	if(this->sufijo > sim.getSufijo())
		return true;

	return false;
}

// Overload: Comparacion
bool Simbolo::operator<(const Simbolo &sim) const
{
	// Comparamos el simbolo
	if(this->sufijo < sim.getSufijo())
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

bool Diccionario::buscarSimbolo(const Simbolo &simbolo, unsigned short &idx, string method)
{
	// Recibe por parametro el simbolo, devuelve el indice en el diccionario
	// en el que se encuentra un simbolo que es igual al pasado por parametro

	if(method == OPT_NORMAL)
	{
		if(busquedaNormal(simbolo, idx))
			return true;

		else
			return false;
	}

	else if(method == OPT_LIST)
	{
		if(busquedaLista(simbolo, idx))
			return true;

		else
			return false;
	}
	else
	{
		if(busquedaArbol(simbolo, idx))
			return true;

		else
			return false;
	}

	return false;
}

bool Diccionario::busquedaNormal (const Simbolo &simbolo, unsigned short &idx)
{
	for(idx = 0; idx < len; idx++)
		{
			if(sim[idx] == simbolo)
				return true;
		}		

	return false;	
}

bool Diccionario::busquedaLista (const Simbolo &simbolo, unsigned short &idx)
{
	// Si el simbolo esta en el dicc ASCII entonces buscamos dir. entre
	// esos simbolos.
	if(simbolo.getPrefijo() == VOID)
		//TODO: idx = (unsigned short)simbolo.getSufijo();
		return busquedaNormal(simbolo, idx);

	// Indice del primer simbolo de la lista. Utilizamos el parametro pasado
	// por referencia para no utilizar otra variable local.
	idx = sim[simbolo.getPrefijo()].getPrimero();

	while(idx != VOID && sim[idx].getSufijo() != simbolo.getSufijo())
		// Iteramos por la lista del prefijo en cuestión.
		idx = sim[idx].getSig();

	// Si encontramos un simbolo entonces idx no será VOID, en caso contrario
	// si sera void. El valor del indice pasado por parametro ya se encuentra
	// establecido debido a la iteración. Por lo tanto solo falta chequear
	// Si es VOID o no para ver si se ha encontrado el elemento o no.
	return (idx != VOID);

}

bool Diccionario::busquedaArbol (const Simbolo &simbolo, unsigned short &idx)
{
	if(simbolo.getPrefijo() == VOID)
		//TODO: idx = (unsigned shrot)simbolo.getSufijo()
		return busquedaNormal(simbolo, idx);
	
	unsigned short nodo = sim[simbolo.getPrefijo()].getPrimero();	

	while (nodo != VOID)
	{
		if (simbolo == sim [nodo])
		{
			idx = nodo;
			return true;
		}

		else if (simbolo < sim [nodo])
			nodo = sim[nodo].getIzquierda();
					
		else
			nodo = sim[nodo].getDerecha(); 
	}			
	
	return false;
}

void Diccionario::agregarSimbolo(Simbolo &simbolo, string method)
{
	// Recibe por parametro el simbolo, lo agrega al diccionario y actualiza el indice.
	// En caso de que el indice agregado sea el ultimo disponible, resetea el diccionario.
	// (No agrega el último pues lo borraría)

	if(indice < len-1)
	{
		if(method == OPT_NORMAL)
		{
			sim[indice] = simbolo;
			indice++;					
		}
		else if(method == OPT_LIST)
		{
			// Guardamos en una variable local el indice del prefijo del simbolo
			unsigned short idx_pref = simbolo.getPrefijo();

			// Seteamos el siguiente de nuestro simbolo, al primero del indice
			// del prefijo del simbolo, si es VOID, es porque era una lista vacia
			// Si no es void, entonces este primer "nodo" ya estara apuntando al siguiente.
			simbolo.setSig(sim[idx_pref].getPrimero());

			// Luego seteamos al nuevo "nodo" para que sea el primer elemento de la lista.
			sim[idx_pref].setPrimero(indice);

			// Guardamos el simbolo en el diccionario
			sim[indice] = simbolo;
			indice++;
		}

		else if (method == OPT_TREE)
		{
			unsigned short idx_pref = simbolo.getPrefijo();

			if (sim[idx_pref].getPrimero() == VOID) 
				sim[idx_pref].setPrimero(indice);

			else {
				unsigned short nodo = sim[idx_pref].getPrimero();	

				while (true)
				{
					if(simbolo < sim[nodo])
					{
						if (sim[nodo].getIzquierda() == VOID)
						{
							sim[nodo].setIzquierda(indice);
							break;
						}
						else
						{
							nodo = sim[nodo].getIzquierda();
							continue;
						}		
					}
					else
					{
						if (sim[nodo].getDerecha() == VOID)
						{
							sim[nodo].setDerecha(indice);
							break;			
						}
						else
						{
							nodo = sim[nodo].getDerecha();
							continue;
						}
					}
				}			

			}
			sim [indice] = simbolo;
			indice ++;
		}

	}
	else
		resetDict();
}

void Diccionario::resetDict()
{
	// Resetea el diccionario dejando unicamente los simbolos correspondientes a los ASCII, es
	// decir los indices entre 0 y 255. Resetea el arreglo de simbolos y el indice.

	for(size_t i = 0; i < MAX_ASCII; i++)
	{
		sim[i].setPrimero(VOID);
	}
	for(size_t i = MAX_ASCII; i < len; i++)
	{
		sim[i].setPrefijo(VOID);
		sim[i].setSufijo(0);
		sim[i].setPrimero(VOID);
		sim[i].setSig(VOID);
		sim[i].setDerecha(VOID);
		sim[i].setIzquierda(VOID);
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
			return ERROR_INDEX_OUT_OF_RANGE;
		}

		// Llamamos nuevamente a la función pero dandole el indice anterior como indice actual (el prefijo del simbolo a crear)
		if( (st = reconstruirCadena(indice_ant, buffer, oss, indice_ant)) != OK)
			return st;

		// Imprimimos el sufijo del buffer (que sera el primer caracter de la cadena del indice anterior previamente pasado)
		if(!(*oss << buffer.getSufijo()))
			return ERROR_WRITE_FILE;

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
			if(!(*oss << sufijo_idx))
				return ERROR_WRITE_FILE;

			return OK;
		}

		// Llamamos nuevamente a la función, sin especificar el parametro indice_ant (no hace falta usarlo), pasando el prefijo del indice
		// como nuevo indice actual de la llamada posterior, de esta manera, obtendremos luego el prefijo del prefijo del indice, hasta que
		// este sea el nulo, en cuyo caso agregamos el sufijo al buffer, imprimimos y retornamos.
		reconstruirCadena(prefijo_idx, buffer, oss);

		// Imprimimos el sufijo del indice.
		if(!(*oss << sufijo_idx))
			return ERROR_WRITE_FILE;

		return OK;
	}		
}
