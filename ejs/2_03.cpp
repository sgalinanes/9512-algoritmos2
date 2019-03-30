#include <random>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>


using namespace std;

void imprimir_matriz(int **A, int n);
int determinant(int **A, int n);
int get_zero_row(int **A, int n);
int count_zeros(int **A, int fila, int n);
int **get_adj(int **A, int n, int i, int j);

int main(void)
{	
	// Dimensiones de la matriz
	int n;
	int **A;

	// Seed
	srand(time(NULL));

	cout << "Ingrese dimensiones de la matriz: ";
	cin >> n;

	// Crear n punteros a enteros.
	A = new int *[n];

	for(int i = 0; i < n; i++)
	{
		// Crear lugar para n enteros en cada uno de esos pteros.
		A[i] = new int[n];
	}

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			A[i][j] = rand() % 10;
			cout << " " << A[i][j] << " ";
		}

		cout << endl;
	}

	int res = determinant(A, n);

	cout << "The determinant is: " << res << endl;

	delete A;
}

int determinant(int **A, int n)
{

	if(n == 2)
	{

		return A[0][0]*A[1][1] - A[0][1]*A[1][0];

	} 
	else if(n < 2)
	{
		cout << "Fatal error" << endl;
		return -1;
	}

	int det = 0;
	// f = fila
	int f = get_zero_row(A, n);
	int a = 0;
	int adj = 0;

	cout << "Preferred row is: " << f << endl;


	for(int j = 0; j < n; j++)
	{
		if(A[f][j] == 0)
		{
			continue;
		}

		a = pow(-1, f+j) * A[f][j];
		int **ADJ = get_adj(A, n, f, j);
		adj = determinant(ADJ, n-1);

		cout << "Agregamos a*adj = " << a*adj << endl;
		det += a*adj;
		cout << "Nuestra suma tiene un valor parcial de: " << det << endl;
	}

	return det;
}

int **get_adj(int **A, int n, int fila, int col)
{

	// CRear nueva matriz con un orden dimensional menor
	int **B = new int *[n-1];

	for(int k = 0; k < n-1; k++)
	{
		B[k] = new int[n-1];
	}

	// Iteradores para la nueva matriz.
	int fil_B = 0; int col_B = 0;

	for(int i = 0; i < n; i++)
	{
		// Si es la fila del valor, saltear la fila.
		if(i == fila)
		{
			continue;
		}

		for(int j = 0; j < n; j++)
		{

			// Si es la columna del valor, saltear la col.
			if(j == col)
			{
				continue;
			}

			// Añadir dato a la nueva matriz
			B[fil_B][col_B] = A[i][j];

			// Pasar a prox col.
			col_B++;

		}
		// Pasar a prox fil, y resetear col.
		fil_B++;
		col_B = 0;
	}

	imprimir_matriz(A, n);
	cout << "Fila: " << fila << ", Columna: " << col << endl;
	imprimir_matriz(B, n-1);
	cout << endl;

	return B;
}

void imprimir_matriz(int **A, int n)
{

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout << " " << A[i][j] << " ";
		}

		cout << endl;
	}
}

int get_zero_row(int **A, int n)
{
	int zs = 0;
	int qty_zeros = 0;
	int row_zeros = 0;
	for(int i = 0; i < n; i++)
	{
		zs = count_zeros(A, i, n);
		if(zs > qty_zeros)
		{
			row_zeros = i;
		}
	}	

	return row_zeros;
}

int count_zeros(int **A, int fila, int n)
{

	int zeros = 0;

	for(int j = 0; j < n; j++)
	{
		if(A[fila][j] == 0)
		{
			zeros++;
		}
	}

	return zeros;
}