#include <iostream>
#include "diccionario.h"

using namespace std;

int main(void)
{
	int option = 0; // 0: compress , 1: decompress
	Diccionario dic;

	Simbolo buffer;

	if(!option)
	{
		int indice;
		unsigned char lec; 		
		
		while(1)
		{
			cin >> lec;

			if(lec == 'q')
			{
				cout << buffer.getPrefijo() << endl;
				break;
			}

			buffer.setSufijo(lec);

			if( (indice = dic.buscarSimbolo(buffer)) == -1)
			{
				// No encontro en el diccionario:
				dic.agregarSimbolo(buffer);
				cout << buffer.getPrefijo() << endl;

				// Buscamos que el indice este dentro de los caracteres originales
				buffer.setPrefijo(VOID);
				indice = dic.buscarSimbolo(buffer);
			}

			buffer.setPrefijo(indice);
		}

		dic.imprimir();

	}
	else
	{
		size_t indice_ant = VOID;
		size_t indice_act = VOID;

		cin >> indice_act;
		// TODO: file IO 
		while(1)
		{
			indice_ant = indice_act;
			cin >> indice_act;

			if(indice_act == VOID)
			{
				break;
			}

			if(dic.checkIndexInASCII(indice_act))
			{

				cout << dic.getSufijoByIndex(indice_act) << endl;
				buffer.setPrefijo(indice_ant);
				buffer.setSufijo(indice_act);
				dic.agregarSimbolo(buffer);

			}
			else
			{
				buffer.setPrefijo(indice_ant);
				dic.imprimirSimbolos(indice_act, buffer);

				buffer.setPrefijo(indice_ant);
				dic.agregarSimbolo(buffer);
				cout << endl;

			}
		}

		dic.imprimir();

	}

	return 0;
}