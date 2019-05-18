#ifndef ERRORS__H
#define ERRORS__H

#define ERROR_1 "Error: Puntero nulo"
#define ERROR_2 "Error: Hubo un problema en la lectura del archivo"
#define ERROR_3 "Error: Indice fuera de rango"
#define ERROR_4 "Error: Formato del archivo a descomprimir incorrecto"
#define ERROR_5 "Error: Hubo un error en la escritura del archivo"

#define MAX_ERRORS 6

void display_error (status_t st);

#endif 