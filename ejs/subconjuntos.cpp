#include <iostream>
#include <cmath>

using namespace std;

template <class T>
class Conjunto
{

	T *p;
	size_t size;

public:

	// Constructores y destructores
	Conjunto()
	{
		this->p = NULL;
		this->size = 0;
	}

	Conjunto(int size)
	{
		this->p = new T[size];
		this->size = size;
	}

	Conjunto(T array[], int size)
	{
		this->p = new T[size];
		this->size = size;

		for(int i = 0; i < size; i++)
		{
			p[i] = array[i];
		}
	}	

	Conjunto(const Conjunto &c)
	{
		this->p = c.p;
		this->size = c.size;
	}
	
	// Métodos
	bool vacio()
	{
		if(p == NULL)
		{
			return true;
		}

		return false;
	}

	T *getList()
	{
		return this->p;
	}

	size_t getSize()
	{
		return this->size;
	}

	void setList(T array[], int size)
	{

		this->p = new T[size];
		this->size = size;

		for(int i = 0; i < size; i++)
		{

			p[i] = array[i];

		}

	}

	void setSize(int size)
	{
		this->size = size;
	}

	void add(T elem)
	{

		int new_sz = (this->size)+1;
		T *cp = new T[new_sz];
		size_t i;

		for(i = 0; i < this->size; i++)
		{
			cp[i] = (this->p)[i];
		}

		cp[i] = elem;


		this->p = cp;
		this->size = new_sz;

	}

	void print()
	{
		cout << "Size: " << this->size;
		cout << "{";
		for(int i = 0; i < this->size; i++)
		{
			cout << (this->p)[i];
		}
		cout << "} ";
	}

};

template <class T>
Conjunto<T>* beta(Conjunto<T> );

template <class T>
Conjunto<T>* combinar(T elem, Conjunto<T>* );

int main(void)
{
	int arr[4] = {1,2,3,4};
	Conjunto<int> a(arr, 4);
	Conjunto<int> *ptr = beta(a);

	for(int i = 0; i < 16; i++)
	{
		ptr[i].print();
		cout << endl;
	}

	delete ptr;
}

template <class T>
Conjunto<T>* beta(Conjunto<T> conj)
{
	cout << "---------------#########--------------------" << endl;
	cout << "Conjunto: ";
	conj.print();
	cout << endl;

	int conj_sz = conj.getSize();
	// Caso base: Conjunto vacio.
	if(conj.vacio())
	{
		Conjunto<T>* a = new Conjunto<T>();
		return a;
	}

	// Creamos un conjunto reducido con n-1 elementos.
	Conjunto<T> reducido;
	if(conj.getSize() != 1)
	{
		reducido = Conjunto<T>(conj.getList() + 1, conj_sz-1);
	}
	else
	{
		reducido = Conjunto<T>();
	}

	cout << "Reducido: ";
	reducido.print();
	cout << endl;

	int reducido_sz = reducido.getSize();
	int subc_sz = pow(2, reducido_sz);
	// Calcular todas los posibles subconjuntos del conjunto.
	Conjunto<T>* subc = beta(reducido);
	
	cout << "-----------------########-------------------" << endl;

	Conjunto<T>* comb = combinar(*(conj.getList()), subc, subc_sz);	

	// Sumar subconjuntos + combinacion del
	// Elemento removido con los subconjuntos.
	int total_sz = pow(2, conj_sz);

	Conjunto<T>* total = new Conjunto<T> [total_sz];
	
	for(int i = 0, j = 0; i < total_sz; i++)
	{
		if(i < subc_sz)
		{
			cout << "Subconjunto: ";
			subc[i].print();
			cout << endl;
			total[i].setList(subc[i].getList(), subc[i].getSize());
		}
		else
		{
			cout << "Combinado: ";
			comb[j].print();
			cout << endl;
			total[i].setList(comb[j].getList(), comb[j].getSize());
			j++;
		}
	}

	// Devolvemos todos los subconjuntos del conjunto
	cout << "Total: " << endl;
	for(int i = 0; i < total_sz; i++)
	{
		cout << "- ";
		total[i].print();
		cout << endl;
	}

	return total;
}

template <class T>
Conjunto<T>* combinar(T elem, Conjunto<T>* lista, int n)
{
	Conjunto<T> *ptr = new Conjunto<T> [n];

	for(int i = 0; i < n; i++)
	{
		ptr[i].setList(lista[i].getList(), lista[i].getSize());
		
		cout << "Combinando... " << endl;
		lista[i].print();
		cout << "Con " << elem << endl;

		ptr[i].add(elem);
		cout << "Resulta... " << endl;
		ptr[i].print();
		cout << endl;
	}

	return ptr;
}

