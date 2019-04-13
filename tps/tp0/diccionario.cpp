#include <iostream>
#include "diccionario.h"

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
/*status_t*/ int Diccionario::buscarSimbolo(const Simbolo &simbolo)
{
	/*
	Recibe por parametro el simbolo, devuelve el indice en el diccionario
	en el que se encuentra un simbolo que es igual al pasado por parametro
	*/

	for(int idx = 0; idx < len; idx++)
	{
		if(sim[idx] == simbolo)
		{
			return idx;
		}
	}

	return -1;
}
// TODO: status_t
/*status_t*/ void Diccionario::agregarSimbolo(const Simbolo &simbolo)
{
	/*
	Recibe por parametro el simbolo, lo agrega al diccionario y actualiza el indice
	*/

	if(indice < len)
	{
		sim[indice] = simbolo;
		indice++;			
	}
	else
	{
		// TODO: Resetear el diccionario
	}

}

void Diccionario::imprimir()
{
	/*
	Imrpime los simbolos contenidos en el diccionario
	*/

	for(int i = 0; i < indice; i++)
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

void Diccionario::imprimirSimbolos(size_t indice, Simbolo &buffer)
{
	/*
	Imprime recursivamente los caracteres "comprimidos",
	y finaliza actualizando el simbolo a agregar al diccionario
	poniendo en su sufijo el primer caracter  correspondiente
	*/

	// TODO: Recursividad de cola
	size_t idx_prefijo = sim[indice].getPrefijo();
	size_t idx_sufijo = sim[indice].getSufijo();

	if(checkIndexInASCII(idx_prefijo))
	{
		buffer.setSufijo(idx_prefijo);
		cout << sim[idx_prefijo].getSufijo();
		cout << sim[idx_sufijo].getSufijo();
		return;
	}

	imprimirSimbolos(idx_prefijo, buffer);
	cout << (int)sim[indice].getSufijo() << "/" << sim[indice].getSufijo();

}