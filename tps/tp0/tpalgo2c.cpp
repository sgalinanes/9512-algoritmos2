#include <iostream>

using namespace std;

#define MAX_ASCII 255
#define MAX_DICT 65535

class Simbolo
{

	size_t prefijo;
	unsigned char sufijo;

public:

	Simbolo()
	{
		prefijo = MAX_DICT; // Refinamiento: VACIO
		sufijo = '\0'; // Refinar
	}

	Simbolo(size_t prefijo, char sufijo)
	{
		this->prefijo = prefijo;
		this->sufijo = sufijo;
	}

	size_t getPrefijo()
	{
		return prefijo;
	}

	char getSufijo()
	{
		return sufijo;
	}

	void setSufijo(char sufijo)
	{
		this->sufijo = sufijo;
	}

	void setPrefijo(size_t prefijo)
	{
		this->prefijo = prefijo;
	}

	bool operator==(const Simbolo &sim)
	{
		if(prefijo == sim.prefijo && sufijo == sim.sufijo)
		{
			return true;
		}

		return false;
	}

	void imprimir()
	{
		cout << "Prefijo: " << prefijo << endl;
		cout << "Sufijo: " << sufijo << endl;
	}

};

class Diccionario
{

	Simbolo sim[MAX_DICT];
	size_t len;
	size_t indice;

public:

	Diccionario()
	{
	for (int i = 0; i < MAX_ASCII+1; i++)
		sim [i].setSufijo(i);


	len = MAX_DICT;
	indice = MAX_ASCII+1;
	}

	int buscarSimbolo(const Simbolo &simbolo)
	{

		for(int i = 0; i < len; i++)
		{
			if(sim[i] == simbolo)
			{
				return i;
			}
		}

		return -1;
	}

	void agregarSimbolo(const Simbolo &simbolo)
	{
		if(indice < len)
		{
			sim[indice] = simbolo;
			indice++;			
		}

	}

	void imprimir()
	{

		for(int i = 0; i < indice; i++)
		{
			cout << "Indice " << i << " ";
			sim[i].imprimir();
		}
	}

};


int main(void)
{

	Diccionario dic;

	Simbolo buffer;

	char c;                      
	int indice;

	while(1)
	{
		cout << "Ingresar caracter: " << endl;
		cin >> c;

		if(c == 'q')
		{
			cout << buffer.getPrefijo() << endl;
			break;
		}

		buffer.setSufijo(c);

		if( (indice = dic.buscarSimbolo(buffer)) == -1)
		{
			// No encontro en el diccionario:
			dic.agregarSimbolo(buffer);
			cout << buffer.getPrefijo() << endl;
			buffer.setPrefijo(MAX_DICT);

			indice = dic.buscarSimbolo(buffer);
		}

		buffer.setPrefijo(indice);



	}

	dic.imprimir();

	return 0;
}