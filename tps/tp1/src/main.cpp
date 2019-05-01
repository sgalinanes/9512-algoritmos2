#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <chrono>

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
	
	// Variable de estado
	status_t st;

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	// Chequeamos que proceso se necesita realizar
	if (process == OPT_COMPRESS) {
		st = compress(iss, oss, method);
		if (st != OK)
			display_error (st);
	}
	else {
		st = decompress(iss, oss, method);
		if (st != OK)
			display_error (st);
	}

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

	cout << "Duration: " << duration << " microseconds" << endl;

	return st;
}

// Chrono code: https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c