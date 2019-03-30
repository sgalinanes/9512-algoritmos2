#include <iostream>


using namespace std;

int C(int n, int k);

int main(void)
{
	int n, k;
	cout << "Pon n y k: " << endl;
	cin >> n;
	cin >> k;

	int res = C(n, k);

	cout << "Resultado: " << res << endl;
}

int C(int n, int k)
{
	if(k == n || k == 0)
	{
		return 1;
	}

	if(n <= 2)
	{
		return n;
	}

	int filaAnterior[n] = {0}; filaAnterior[0] = 1; filaAnterior[1] = 1;
	int fila[n] = {0};
	for(int i = 1; i < n; i++)
	{

		fila[0] = 1; fila[i+1] = 1;

		for(int j = 1; j < i+1; j++)
		{

			fila[j] = filaAnterior[j-1] + filaAnterior[j];
			if(i == n-1 && j == k)
			{
				return fila[j];
			}
		}

		for(int ctr = 0; ctr < n; ctr++)
		{
			filaAnterior[ctr] = fila[ctr];
			if(filaAnterior[ctr] == 0)
			{
				break;
			}

			cout << " " << filaAnterior[ctr] << " ";
		}

		cout << endl;

		

	}

	return -1;

}