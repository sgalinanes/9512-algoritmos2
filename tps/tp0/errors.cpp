#include <iostream>
#include "types.h"
#include "errors.h"

using namespace std;

string error_dictionary [4] = { "",
                            ERROR_1, 
                            ERROR_2, 
                            ERROR_3};


void display_error (status_t st)
{
    cerr << error_dictionary [st] << endl;
}
