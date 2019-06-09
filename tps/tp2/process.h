#ifndef PROCESS__H
#define PROCESS__H

#include "types.h"

#define TOKEN_SEPARATOR	','

status_t decompress(istream *, ostream *, string);
status_t compress(istream *, ostream *, string);

#endif