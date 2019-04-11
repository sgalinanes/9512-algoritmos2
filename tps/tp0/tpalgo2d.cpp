#include <iostream>

using namespace std;


class Simbolo
{

	size_t prefijo;
	unsigned char sufijo;

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
		cout << "Sufijo: " << (int)sufijo << "/" << sufijo  << endl;
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

	// cabiar nombre del metodo!
	unsigned char getPos(size_t indice)
	{

		if(indice > len)
		{
			return 255;
		}

		return sim[indice].getSufijo();

	}

	bool checkIndex(size_t indice)
	{

		if(indice > 2)
		{
			return false;
		}

		return true;

	}

	void imprimirSimbolos(size_t indice, Simbolo &buffer)
	{

		size_t idx_prefijo = sim[indice].getPrefijo();
		unsigned char idx_sufijo = sim[indice].getSufijo();

		if(checkIndex(idx_prefijo))
		{
			buffer.setSufijo(idx_prefijo);
			cout << (int)sim[idx_prefijo].getSufijo() << "/" << sim[idx_prefijo].getSufijo();
			cout << (int)sim[idx_sufijo].getSufijo() << "/" << sim[idx_sufijo].getSufijo();
			return;
		}

		imprimirSimbolos(idx_prefijo, buffer);
		cout << (int)sim[indice].getSufijo() << "/" << sim[indice].getSufijo();

	}

};


int main(void)
{

	Diccionario dic;

	Simbolo buffer;
	size_t indice_ant = 255;
	size_t indice_act;

	cin >> indice_act;

	cout << (int)dic.getPos(indice_act) << "/" << dic.getPos(indice_act) << endl;

	while(1)
	{
		indice_ant = indice_act;
		cin >> indice_act;

		if(indice_act == 255)
		{
			break;
		}

		if(dic.checkIndex(indice_act))
		{

			cout << (int)dic.getPos(indice_act) << "/" << dic.getPos(indice_act) << endl;
			buffer.setPrefijo(indice_ant);
			buffer.setSufijo(indice_act);
			dic.agregarSimbolo(buffer);

		}
		else
		{

			dic.imprimirSimbolos(indice_act, buffer);
			dic.agregarSimbolo(buffer);
			cout << endl;

		}
	}

	dic.imprimir();

	return 0;
}