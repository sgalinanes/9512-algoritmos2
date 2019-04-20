#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

#include "main.h"
#include "types.h"
#include "diccionario.h"
#include "cmdline.h"
#include "process.h"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_process(string const &);

static string process;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "process", "-", opt_process, OPT_DEFAULT},
	{0, },
};

static void
opt_input(string const &arg)
{
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in);
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
		ofs.open(arg.c_str(), ios::out);
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

		if ( (process != OPT_COMPRESS && process != OPT_DECOMPRESS))
		{
			cerr << "invalid process "
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

	if(process == OPT_COMPRESS)
		st = compress(iss, oss);
	else
		st = decompress(iss, oss);

	//cout << "State returned: " << st << endl;
	return st;
}