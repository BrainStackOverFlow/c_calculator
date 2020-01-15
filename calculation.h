#ifndef calculator_calculation_h
#define calculator_calculation_h

#include "utilities.h"

enum EOperation 
{
	EOperation_Nop = 0,
	EOperation_Addition,
	EOperation_Substract,
	EOperation_Multiply,
	EOperation_Divide,
	EOperation_Xor,
	EOperation_ShiftRight,
	EOperation_ShiftLeft,
	EOperation_RotateRight,
	EOperation_RotateLeft,
	EOperation_ChangeBase,
	EOperation_ExitProgram,
	EOperation_NumOfOperations,
	EOperation_FirstOperation = EOperation_Addition
};

char* EOperation_ToString[];

int operationUsesOneOperand(enum EOperation op);

int operationUsesTwoOperands(enum EOperation op);

// does the operation op on the numbers a, b
enum EStatus calculate_result(int a, int b, enum EOperation op, int *result);

enum EStatus change_base(int a, enum EBase* base);

#endif