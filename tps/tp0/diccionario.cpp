#include <iostream>
#include "diccionario.h"
#include "types.h"

using namespace std;

// CLASE SIMBOLO //
// ## --- Constructores --- ## //
Simbolo::Simbolo()
{
	// Inicializar el prefijo a vacio y el sufijo (por def.) al caracter nulo
	prefijo = VOID;
	sufijo = 0;
}

Simbolo::Simbolo(size_t prefijo, unsigned char sufijo)
{
	this->prefijo = prefijo;
	this->sufijo = sufijo;
}

// ## --- Metodos --- ## //

// Getters
size_t Simbolo::getPrefijo()
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

void Simbolo::setPrefijo(size_t prefijo)
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
Diccionario::Diccionario()
{
	for(size_t i = 0; i < MAX_ASCII; i++)
		// En los primeros 256 lugares, copia los simbolos ASCII correspondientes.
		sim[i].setSufijo(i);

	len = MAX_DICT;
	indice = MAX_ASCII;
}

// ## --- Metodos --- ## //
size_t Diccionario::getIndice()
{
	return this->indice;
}

bool Diccionario::buscarSimbolo(const Simbolo &simbolo, size_t &idx)
{
	// Recibe por parametro el simbolo, devuelve el indice en el diccionario
	// en el que se encuentra un simbolo que es igual al pasado por parametro

	for(idx = 0; idx < len; idx++)
	{
		if(sim[idx] == simbolo)
			return true;
	}

	return false;
}

void Diccionario::agregarSimbolo(const Simbolo &simbolo)
{
	//Recibe por parametro el simbolo, lo agrega al diccionario y actualiza el indice
	//En caso de que el indice agregado sea el ultimo disponible, resetea el diccionario.
	//(No agrega el último pues ahora hara el reseteo)

	if(indice < len-1)
	{
		sim[indice] = simbolo;
		indice++;		
	}
	else
		this->resetDict();

}

void Diccionario::resetDict()
{
	//Resetea el diccionario dejando unicamente los simbolos correspondientes a los ASCII, es
	//decir los indices entre 0 y 255. Resetea el largo, el arreglo de simbolos y el indice.

	for(size_t i = MAX_ASCII; i < len; i++)
	{
		sim[i].setPrefijo(VOID);
		sim[i].setSufijo(0);
	}

	indice = MAX_ASCII;
}

void Diccionario::imprimir()
{
	//Imrpime los simbolos contenidos en el diccionario

	for(size_t i = MAX_ASCII; i < indice; i++)
	{
		cout << "Indice " << i << " ";
		sim[i].imprimir();
	}
}
// TODO: status_t
/* status_t */ unsigned char Diccionario::getSufijoByIndex(size_t indice)
{
	//Devuelve el sufijo del indice del diccionario pasado por parametro

	if(indice > len)
	{
		// TODO: Devolver un status_t que indique que el indice esta fuera de bounds.
		return 0;
	}

	return sim[indice].getSufijo();

}


bool Diccionario::checkIndexInASCII(size_t indice)
{
	// Chequea si el indice esta entre los ASCII 

	if(indice >= MAX_ASCII)
		return false;

	return true;

}

bool Diccionario::checkIndex(size_t indice)
{
	// Chequea si el indice esta en el diccionario entero

	if(indice >= this->indice)
		return false;

	return true;
}

/*
status_t Diccionario::imprimirSimbolos(size_t indice_ant, size_t indice_act, Simbolo &buffer, ostream *oss)
{
	//Imprime recursivamente los caracteres "comprimidos",
	//y finaliza actualizando el simbolo a agregar al diccionario
	//poniendo en su sufijo el primer caracter  correspondiente

	// TODO: Recursividad de cola
	if(oss == NULL)
		return ERROR_NULL_POINTER;

	if(!checkIndex(indice_act))
	{
		imprimirSimbolos(indice_ant, indice_ant, buffer, oss);
		imprimirPrefijo(indice_ant, oss);
		return OK;
	}

	size_t idx_prefijo = sim[indice_act].getPrefijo();
	size_t idx_sufijo = sim[indice_act].getSufijo();

	if(checkIndexInASCII(idx_prefijo))
	{
		buffer.setSufijo(idx_prefijo);
		*oss << sim[idx_prefijo].getSufijo();
		*oss << sim[idx_sufijo].getSufijo();
		return OK;
	}

	imprimirSimbolos(indice_ant, idx_prefijo, buffer, oss);
	*oss << sim[indice_act].getSufijo();

	return OK;
}

status_t Diccionario::imprimirSimbolos(size_t indice, ostream *oss)
{
	if(oss == NULL)
		return ERROR_NULL_POINTER;

	if(indice > this->indice)
		return ERROR_INDEX_OUT_OF_RANGE;

	*oss << sim[indice].getSufijo();

	return OK;
}

status_t Diccionario::imprimirPrefijo(size_t indice, ostream *oss)
{
	if(oss == NULL)
		return ERROR_NULL_POINTER;

	size_t pref = sim[indice].getPrefijo();

	while(!checkIndexInASCII(pref))
		pref = sim[pref].getPrefijo();

	*oss << (unsigned char)pref;

	return OK;
}
*/

status_t Diccionario::reconstruirCadena(size_t indice_act, Simbolo &buffer, ostream *oss, size_t indice_ant = VOID)
{

	// Chequeamos si el indice esta en el diccionario
	if(!checkIndex(indice_act))
	{
		// Si el indice anterior es igual al indice actual entonces tenemos un error: Ni el indice anterior ni el actual
		// pertenecen al diccionario, entonces no podemos realizar la reconstruccion (la data es erronea).
		if(indice_ant == indice_act)
		{
			status_t st = ERROR_WRONG_COMPRESSION;
			return st;			
		}

		// Llamamos nuevamente a la función pero dandole el indice anterior como indice actual (el prefijo del simbolo a crear)
		reconstruirCadena(indice_ant, buffer, oss, indice_ant);

		// Imprimimos el sufijo del buffer (que sera el primer caracter de la cadena del indice anterior previamente pasado)
		*oss << buffer.getSufijo();

		return OK;

	}
	else
	{
		// Creamos variables para el prefijo y sufijo del indice al que accedemos.
		size_t prefijo_idx = sim[indice_act].getPrefijo();
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