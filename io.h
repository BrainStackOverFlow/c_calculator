#ifndef calculator_io_h
#define calculator_io_h

#include "calculation.h"
#include "utilities.h"

// inputs the operation
enum EStatus get_op(enum EOperation* op);

// input 1 number for the program from stdin
enum EStatus get_number(int* x, enum EBase base);

enum EStatus get_input(int* a, int* b, enum EOperation op, enum EBase base);

#endif