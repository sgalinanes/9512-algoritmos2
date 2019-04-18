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
	{
		return true;
	}

	return false;
}




// CLASE DICCIONARIO //
// ## --- Constructores --- ## //
Diccionario::Diccionario()
{
	for(int i = 0; i < MAX_ASCII; i++)
	{
		// En los primeros 256 lugares, copia los simbolos ASCII correspondientes.
		sim[i].setSufijo(i);
	}

	len = MAX_DICT;
	indice = MAX_ASCII;
}

// ## --- Metodos --- ## //
// TODO: status_t
status_t Diccionario::buscarSimbolo(const Simbolo &simbolo, size_t &idx)
{
	/*
	Recibe por parametro el simbolo, devuelve el indice en el diccionario
	en el que se encuentra un simbolo que es igual al pasado por parametro
	*/

	for(idx = 0; idx < len; idx++)
	{
		if(sim[idx] == simbolo)
		{
			return OK;
		}
	}

	return SYMBOL_NOT_FOUND;
}
// TODO: status_t
/*status_t*/ void Diccionario::agregarSimbolo(const Simbolo &simbolo)
{
	/*
	Recibe por parametro el simbolo, lo agrega al diccionario y actualiza el indice
	En caso de que el indice agregado sea el ultimo disponible, resetea el diccionario.
	(No agrega el último pues ahora hara el reseteo)
	*/
	if(indice < len-1)
	{
		sim[indice] = simbolo;
		indice++;		
	}
	else
	{

		this->resetDict();

	}

}

void Diccionario::resetDict()
{

	/* 
	Resetea el diccionario dejando unicamente los simbolos correspondientes a los ASCII, es
	decir los indices entre 0 y 255. Resetea el largo, el arreglo de simbolos y el indice.
	*/

	for(int i = MAX_ASCII; i < len; i++)
	{
		sim[i].setPrefijo(VOID);
		sim[i].setSufijo(VOID);
	}

	indice = MAX_ASCII;


}

void Diccionario::imprimir()
{
	/*
	Imrpime los simbolos contenidos en el diccionario
	*/

	for(int i = MAX_ASCII; i < indice; i++)
	{
		cout << "Indice " << i << " ";
		sim[i].imprimir();
	}
}
// TODO: status_t
/* status_t */ unsigned char Diccionario::getSufijoByIndex(size_t indice)
{
	/*
	Devuelve el sufijo del indice del diccionario pasado por parametro
	*/

	if(indice > len)
	{
		// TODO: Devolver un status_t que indique que el indice esta fuera de bounds.
		return 0;
	}

	return sim[indice].getSufijo();

}


bool Diccionario::checkIndexInASCII(size_t indice)
{
	/*
	Chequea si el indice esta entre los ASCII 
	*/

	if(indice >= MAX_ASCII)
	{
		return false;
	}

	return true;

}

bool Diccionario::checkIndex(size_t indice)
{
	/* Chequea si el indice esta en el diccionario entero
	*/

	if(indice >= this->indice)
	{
		return false;
	}

	return true;
}

void Diccionario::imprimirSimbolos(size_t indice, Simbolo &buffer, ostream *oss)
{
	/*
	Imprime recursivamente los caracteres "comprimidos",
	y finaliza actualizando el simbolo a agregar al diccionario
	poniendo en su sufijo el primer caracter  correspondiente
	*/

	// TODO: Recursividad de cola
	if(oss == NULL)
	{
		//TODO: status_t
		return;
	}

	size_t idx_prefijo = sim[indice].getPrefijo();
	size_t idx_sufijo = sim[indice].getSufijo();

	if(checkIndexInASCII(idx_prefijo))
	{
		buffer.setSufijo(idx_prefijo);
		*oss << sim[idx_prefijo].getSufijo();
		*oss << sim[idx_sufijo].getSufijo();
		return;
	}
	imprimirSimbolos(idx_prefijo, buffer, oss);
	*oss << sim[indice].getSufijo();

}