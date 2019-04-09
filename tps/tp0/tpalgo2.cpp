#include <iostream>

using namespace std;


class Simbolo
{

	size_t prefijo;
	char sufijo;

public:

	Simbolo()
	{
		prefijo = 255;
		sufijo = 255;
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

	Simbolo sim[8];
	size_t len;
	size_t indice;

public:

	Diccionario()
	{
		sim[0] = Simbolo(255, 'A');	
		sim[1] = Simbolo(255, 'B');	
		sim[2] = Simbolo(255, 'C');	

		len = 8;
		indice = 3;
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

		sim[indice] = simbolo;
		indice++;

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
			buffer.setPrefijo(255);

			indice = dic.buscarSimbolo(buffer);
		}

		buffer.setPrefijo(indice);



	}

	dic.imprimir();

	return 0;
}