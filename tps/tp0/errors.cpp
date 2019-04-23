	#include <iostream>
#include "types.h"
#include "errors.h"

using namespace std;

string error_dictionary [MAX_ERRORS] = { 
							"",
                            ERROR_1, 
                            ERROR_2, 
                            ERROR_3,
                            ERROR_4
                        };


void display_error (status_t st)
{
    cerr << error_dictionary [st] << endl;
}
