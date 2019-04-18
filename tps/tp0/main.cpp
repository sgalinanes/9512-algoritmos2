#include <iostream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "types.h"
#include "diccionario.h"
#include "cmdline.h"
// Prueba de la clase cmdline: dado un factor entero pasado por la
// línea de comando, leemos una secuencia de números que ingresan
// por la entrada estándar, los multiplicamos por ese factor, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $
#define OPT_COMPRESS 	"compress"
#define OPT_DECOMPRESS 	"decompress"

#define TOKEN_SEPARATOR	','

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_process(string const &);
void decompress(istream *, ostream *);
void compress(istream *, ostream *);

// Tabla de opciones de línea de comando. El formato de la tabla
// consta de un elemento por cada opción a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opción lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opción.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opción en caso que no esté explícitamente presente
//   en la línea de comandos del programa. Si la opción no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al método de parseo de la opción,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La última columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opción: cuando la
//   opción es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la última entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "process", "-", opt_process, OPT_DEFAULT},
	{0, },
};

static string process;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)



/*****************************************************/

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
		cout << "INPUT STD" << endl;
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
		cout << "INPUT =" << iss << endl;
	}

	// Verificamos que el stream este OK.
	//
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
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
		cout << "OUTPUT STD" << endl;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
		cout << "OUTPUT =" << oss << endl;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_process(string const &arg)
{
	istringstream iss(arg);

	// Intentamos extraer el factor de la línea de comandos.
	// Para detectar argumentos que únicamente consistan de
	// números enteros, vamos a verificar que EOF llegue justo
	// después de la lectura exitosa del escalar.
	//
	/*
	if (iss.bad()) {
		cerr << "cannot read process."
		     << endl;
		exit(1);
	} 
	*/

	if (arg == "-")
	{
		process = OPT_COMPRESS;
		cout << "default PROCESS =" << process << endl;

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
		cout << "PROCESS =" << process << endl;
	}
}

int main(int argc, char * const argv[])
{
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
	

	if(process == OPT_COMPRESS)
	{
		//TODO: status_t
		compress(iss, oss);

	}
	else
	{
		//TODO: status_t
		decompress(iss, oss);
	}

	return 0;
}

void compress(istream *iss, ostream *oss)
{	
	// Chequear punteros nulos
	if(iss == NULL || oss == NULL)
	{
		//TODO: ret status_t
		return;
	}

	// Crear diccionario; Simbolo (para lectura/insercion) en diccionario y status_t.
	Diccionario dic;
	Simbolo buffer;
	status_t st;
	bool read = false;

	// Crear variable indice y variable de lectura.
	size_t indice;
	unsigned char lec; 	

	while(*iss >> lec)
	{
		//cout << "Leo: " << lec << ": ";
		// Parseamos lo leido al sufijo del buffer
		buffer.setSufijo(lec);

		// Buscamos si el símbolo se encuentra en el diccionario.
		if( (st = dic.buscarSimbolo(buffer, indice)) != OK)
		{
			// Caso: No se encontro en el diccionario

			// Agregamos el buffer al diccionario
			
			dic.agregarSimbolo(buffer);

			// Envíamos el prefijo a la salida (std o archivo)
			*oss << buffer.getPrefijo() << TOKEN_SEPARATOR;

			// Buscamos el indice del sufijo
			indice = (size_t)buffer.getSufijo();
		}
		else
		{
			//cout << "Encontre en: " << indice;
		}
		// Agregamos el indice del encontrado o el agregado
		if(st != OK)
		{
			//cout << "Agrego: " << dic.getIndice()-1 << ": [ " << buffer.getPrefijo() << " | " << buffer.getSufijo() << " ]";
			//cout << " Impr: " << buffer.getPrefijo();

		}
		buffer.setPrefijo(indice);


		//cout << endl;
	}

	// Chequeamos si el bit fail esta encendido y el EOF no fue leído
	if(!iss->eof() && iss->fail())
	{
		// TODO: funcion de error u algo
		cout << "Ocurrio un error al realizar la lectura del archivo" << endl;
	}
	else
	{
		// Imprimimos el ultimo prefijo (al llegar a EOF)
		*oss << buffer.getPrefijo() << endl;		
	}

}

void decompress(istream *iss, ostream *oss)
{
	// Creamos un diccionario y un simbolo buffer
	Diccionario dic;
	Simbolo buffer;

	// Inicializamos los indices a vacío.
	size_t indice_ant = VOID;
	size_t indice_act = VOID;

	// Utilizamos este caracter para leer los separadores.
	char c;

	// Primer caracter (no se agrega nada al diccionario):
	if(*iss >> indice_act)
	{
		*oss << dic.getSufijoByIndex(indice_act);
		indice_ant = indice_act;
		*iss >> c;
	}
	else
	{
		// TODO: error
		cout << "Error" << endl;
	}

	// Comenzamos la lectura (desde el segundo)
	while(*iss >> indice_act)
	{

		if(dic.checkIndex(indice_act))
		{	
			buffer.setPrefijo(indice_ant);
			if(dic.checkIndexInASCII(indice_act))
			{
				buffer.setSufijo(indice_act);			
				dic.imprimirSimbolos(indice_act, oss);
			}
			else
			{
				dic.imprimirSimbolos(indice_ant, indice_act, buffer, oss);
			}

			dic.agregarSimbolo(buffer);					

		}
		else
		{
			buffer.setPrefijo(indice_ant);
			dic.imprimirSimbolos(indice_ant, indice_act, buffer, oss);
			dic.agregarSimbolo(buffer);
		}

		indice_ant = indice_act;
		*iss >> c;
	}

}


			/*
			if(dic.checkIndexInASCII(indice_act))
			{
				*oss << dic.getSufijoByIndex(indice_act);
				buffer.setPrefijo(indice_ant);
				buffer.setSufijo(indice_act);
				dic.agregarSimbolo(buffer);

			}
			else
			{
				buffer.setPrefijo(indice_ant);			
				dic.imprimirSimbolos(indice_act, buffer, oss);

				//buffer.setPrefijo(indice_ant);
				dic.agregarSimbolo(buffer);

			}
			*/