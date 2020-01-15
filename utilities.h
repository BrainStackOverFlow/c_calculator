#ifndef calculator_utilities_h
#define calculator_utilities_h

#define sizeof_inbits(t) (sizeof(t)*8)

enum EStatus 
{
	EStatus_Success = 0,
	EStatus_GeneralError,
	EStatus_CalculationError,
	EStatus_Overflow,
	EStatus_DivideByZero,
	EStatus_IOError,
	EStatus_BadInput,
	EStatus_BadOpInput,
	EStatus_BadBaseInput,
	EStatus_NullReferenceError,
	EStatus_OperationNotValid,
	EStatus_NumOfErrors
};

char* EStatus_ToString[];

enum EBase
{
	EBase_Binary = 2,
	EBase_Octal = 8,
	EBase_Decimal = 10,
	EBase_Hexadecimal = 16
};

// check if a string is a integer
int isinteger(char* s, enum EBase b);

// u need to deallocate the string returned with free()
// on error returns null
char* int_to_base_string(int a, enum EBase b);

// handle program errors
int handle_error(enum EStatus s);

#endif