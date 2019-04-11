#include <iostream>

#define LEN 3

using namesapce std;

int main(void)
{

	vector<int> v = {1, 2, 3};

	permutacion(vector);

}

int factorial(int n)
{
	if(n == 0)
	{
		return 1;
	}

	return n * factorial(n-1);
}

int permutacion(int& **perm, vector<int> v)
{
	if(v.size() == 1)
	{
		return v[0];
	}

	for(int i = 0; i < factorial(v.size()); i++)
	{

		// perm[i] = v[i] + permutacion(perm, v) <- v es el vector
		//											sin v[i]

	}

}