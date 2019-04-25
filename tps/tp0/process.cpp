#include <iostream>
#include <fstream>

#include "types.h"
#include "diccionario.h"
#include "process.h"

status_t compress(istream *iss, ostream *oss)
{	
	// Si alguno de los punteros es nulo retornamos un error.
	if(iss == NULL || oss == NULL)
		return ERROR_NULL_POINTER;	

	// Inicializamos el diccionario.
	Diccionario dic;

	// Inicializamos un Símbolo buffer, será el que relacione lo leído con el diccionario
	Simbolo buffer;

	// Inicializamos variables para la lectura
	size_t indice;
	unsigned char lec; 	
	char c;

	// Leemos cualquier char del input con la funcion get
	while(iss->get(c))
	{
		// Casteamos el char leído a unsigned char 
		lec = static_cast<unsigned char>(c);

		// Parseamos lo leido al sufijo del buffer
		buffer.setSufijo(lec);

		// Buscamos si el símbolo se encuentra en el diccionario.
		// pasando el indice por referencia y retornando el indice
		// encontrado en caso de que fuera encontrado.
		if(!dic.buscarSimbolo(buffer, indice))
		{
			// Caso: No se encontro en el diccionario
			// Agregamos el buffer al diccionario			
			dic.agregarSimbolo(buffer);

			// Envíamos el prefijo a la salida (std o archivo)
			// con un char como separador (usualmente una coma)
			*oss << buffer.getPrefijo() << TOKEN_SEPARATOR;

			// Buscamos el indice del sufijo, lo necesitaremos para agregarlo
			// como prefijo del buffer en la proxima iteracion.
			indice = (size_t)buffer.getSufijo();
		}

		// Agregamos el indice del simbolo encontrado o agregado al diccionario.
		buffer.setPrefijo(indice);
	}

	// Chequeamos si el bit fail esta encendido y el EOF no fue leído
	if(!iss->eof() && iss->fail())
        return ERROR_READ_FILE;

	else
		// Chequeamos que el prefijo no sea void, podria suceder que el archivo este vacio por lo que
		// nunca entra a la loop de lectura y el prefijo sigue siendo VOID pues nunca se actualizo.
		if(buffer.getPrefijo() != VOID)
		{
			// Imprimimos el ultimo prefijo (al llegar a EOF)
			*oss << buffer.getPrefijo() << endl;			
		}


    return OK;		
}

status_t decompress(istream *iss, ostream *oss)
{
	if(iss == NULL || oss == NULL)
		return ERROR_NULL_POINTER;	
	
	// Inicializamos el diccionario
	Diccionario dic;

	// Inicializamos un Símbolo buffer, será el que relacione lo leído con el diccionario
	Simbolo buffer;
    status_t st;

	// Inicializamos los indices a vacío.
	size_t indice_ant = VOID;
	size_t indice_act = VOID;

	// Utilizamos este caracter para leer los separadores.
	char c;

	// Para el primer indice no se agrega nada al diccionario, lo tratamos aparte.
	if(*iss >> indice_act)
	{
		// Buscamos el sufijo dado el indice
		unsigned char sfx;
		if( (st = dic.getSufijoByIndex(indice_act, sfx)) != OK)
		{
			return st;
		}

		// Imprimimos el sufijo
		*oss << sfx;

		// Actualizamos el indice
		indice_ant = indice_act;

		// Salteamos el separador
		*iss >> c;
		if(c != TOKEN_SEPARATOR)
			return ERROR_FILE_FORMAT;
	}
	else // Ocurrio un error al leer el indice
        return ERROR_READ_FILE;

	// Comenzamos la lectura iterativamente.
	while(*iss >> indice_act)
	{
		// Agregamos el indice anterior al prefijo del buffer.
		buffer.setPrefijo(indice_ant);

		// Llamamos a la función reconstruir cadena para realizar la insercion del sufijo en el buffer y la impresión
		// de la cadena comprimida.
		if( (st = dic.reconstruirCadena(indice_act, buffer, oss, indice_ant)) != OK)
		{
			return st;
		}
		// Agregamos el simbolo al diccionario
		dic.agregarSimbolo(buffer);

		// Actualizamos el indice para la proxima iteracion
		indice_ant = indice_act;

		// Salteamos el separador.
		*iss >> c;
		if(c != TOKEN_SEPARATOR)
			return ERROR_FILE_FORMAT;
	}

	// Chequeamos si el bit fail esta encendido y el EOF no fue leído
	if(!iss->eof() && iss->fail())
        return ERROR_READ_FILE;

    return OK;
}