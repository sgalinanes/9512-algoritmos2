#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <random>

#include "types.h"
#include "diccionario.h"
#include "cmdline.h"
#include "process.h"
#include "errors.h"

#define OPT_COMPRESS "compress"
#define OPT_DECOMPRESS	"decompress"

#define OPT_NORMAL "normal"
#define OPT_LIST "list"
#define OPT_TREE "tree" 

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_process(string const &);
static void opt_method(string const &);

static string process;
static string method;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "process", "-", opt_process, OPT_DEFAULT},
	{1, "m", "method", "-", opt_method, OPT_DEFAULT},
	{0, },
};

static void
opt_input(string const &arg)
{
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		// Cambio: ios::in a ios::binary
		ifs.open(arg.c_str(), ios::in | ios::binary);
		iss = &ifs;
	}

	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		// Cambio: ios::out a ios::binary
		ofs.open(arg.c_str(), ios::out | ios::binary);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_process(string const &arg)
{
	if (arg == "-")	{
		process = OPT_COMPRESS;
	} else {
		process = arg;

		if ((process != OPT_COMPRESS && process != OPT_DECOMPRESS))
		{
			cerr << "invalid process "
		    	 << arg
		     	<< "."
		     	<< endl;
			exit(1);		
		}
	}
}

static void
opt_method(string const &arg)
{
	if (arg == "-")	{
		method = OPT_NORMAL;
	} else {
		method = arg;

		if ((method != OPT_LIST && method != OPT_TREE && method != OPT_NORMAL))
		{
			cerr << "invalid method "
		    	 << arg
		     	<< "."
		     	<< endl;
			exit(1);		
		}
	}
}


int main(int argc, char * const argv[])
{
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

	status_t st;
	
	if(iss != &cin)
	{
		cerr << "Error: Prueba de tiempo requiere que no haya argumentos de entrada" << endl;
		return 255;
	}

	srand(time(NULL));
	int TOTAL_TESTS = 20;
	stringstream ss;

	ss << "resultados_" << method << ".csv";
	ofstream resultados(ss.str(), ofstream::out | ofstream::app);
	ss.str("");

	for(int i = 0; i < TOTAL_TESTS; i++)
	{	
		// Abrimos archivo de entrada (vamos a copiar valores y luego
		// comprimirlos, asi que necesitamos un fstream)
		ss << "entrada_" << i << ".txt";
		ofstream temp(ss.str(), ofstream::out | ofstream::app | ofstream::binary);

		// Cantidad de bytes a comprimir
		int n = 1000*(i+1);

		// Buffer
		unsigned char *buffer = new unsigned char[n];

		if(temp)
		{

			// Creamos un buffer con n random unsigned chars
			for(int j = 0; j < n; j++)
			{
				buffer[j] = rand() % 256;

			}

			// Enviamos el buffer al archivo para que el programa lo comprima
			temp.write((char *)buffer, n);

			// Cerramos el archivo temmporal
			temp.close();			
		}
		else
		{
			st = ERROR_READ_FILE;
			display_error(st);
		}
	
		// Abrimos ahora el archivo pero como entrada.
		ifstream entrada(ss.str(), ifstream::in | ifstream::binary);
		if(entrada)
			iss = &entrada;
		else
		{
			st = ERROR_READ_FILE;
			display_error(st);
		}

		// Clear el stringstream
		ss.str("");


		//--------------- COMIENZO COMPRESION ---------------------//
		
		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		// Chequeamos que proceso se necesita realizar
		if (process == OPT_COMPRESS) {
			st = compress(iss, oss, method);
			if (st != OK)
			{
				display_error (st);
				return st;
			}
		}
		else {
			st = decompress(iss, oss, method);
			if (st != OK)
			{
				display_error (st);
				return st;
			}
		}

		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		
		//--------------- FIN COMPRESION  --------------------------//


		auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

		// Enviamos los datos al archivo de resultados
		resultados << n << "," << duration << endl;

		// Cerramos el archivo de entrada, y dejamos sin uso la memoria pedida.
		entrada.close();
		delete [] buffer;

	}
	resultados.close();
	return st;
}

// Chrono code: https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c