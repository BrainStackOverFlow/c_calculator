#include "calculation.h"

#include <stddef.h>

char* EOperation_ToString[] = 
{
	"Nop",
	"Addition",
	"Substract",
	"Multiply",
	"Divide",
	"Xor",
	"Shift right",
	"Shift left",
	"Rotate right",
	"Rotate left",
	"Change Base",
	"Exit Program"
};

int operationUsesOneOperand(enum EOperation op)
{
	if (0)
	{
		return 1;
	}
	return 0;
}

int operationUsesTwoOperands(enum EOperation op)
{
	if (EOperation_Addition <= op && op <= EOperation_RotateLeft)
	{
		return 1;
	}
	return 0;
}


enum EStatus addition(int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = a + b;

	if(((a < 0) && (b < 0) && (*result > 0)) || ((a > 0) && (b > 0) && (*result < 0))) // if overflow accured
	{ 
        return EStatus_Overflow; 
    }

    return EStatus_Success; 
}

enum EStatus substraction(int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = a - b;

	if (((a < 0) && (0 < b) && (0 < *result)) || ((0 < a) && (b < 0) && (*result < 0))) 
	{
		return EStatus_Overflow;
	}

    return EStatus_Success; 
}

enum EStatus multiply(int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = a * b;

	if (a != 0 && *result / a != b) // if overflow accured
	{ 
    	return EStatus_Overflow;
	}

	return EStatus_Success;
}

enum EStatus division(int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	if(b != 0) 
	{
		*result = a / b;
		return EStatus_Success;
	}
	return EStatus_DivideByZero;
}

enum EStatus xor(int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = a ^ b;

	return EStatus_Success;
}

enum EStatus shit_right (int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = a >> b;

	return EStatus_Success;
}

enum EStatus shit_left (int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = a << b;

	return EStatus_Success;
}

enum EStatus rotate_right (int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = (a >> b % sizeof_inbits(int)) | (a << (sizeof_inbits(int)-b) % sizeof_inbits(int));

	return EStatus_Success;
}

enum EStatus rotate_left (int a, int b, int* result)
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	*result = (a << b % sizeof_inbits(int)) | (a >> (sizeof_inbits(int)-b) % sizeof_inbits(int));

	return EStatus_Success;
}

enum EStatus calculate_result(int a, int b, enum EOperation op, int *result) 
{
	if (result == NULL)
	{
		return EStatus_NullReferenceError;
	}

	enum EStatus status = EStatus_Success;

	switch(op)
	{
		case EOperation_Addition: // does addition on a, b
		{
			status = addition(a, b, result);
		} break;

		case EOperation_Substract: //does substraction on a, b
		{
			status = substraction(a, b, result);
		} break;

		case EOperation_Multiply: //does multiplication on a, b
		{
			status = multiply(a, b, result);
		} break;
			
		case EOperation_Divide: //does division on a, b 
		{
			status = division(a, b, result);
		} break;

		case EOperation_Xor:
		{
			status = xor(a, b, result);
		} break;

		case EOperation_ShiftRight:
		{
			status = shit_right(a, b, result);
		} break;

		case EOperation_ShiftLeft:
		{
			status = shit_left(a, b, result);
		} break;

		case EOperation_RotateRight:
		{
			status = rotate_right(a, b, result);
		} break;
		
		case EOperation_RotateLeft:
		{
			status = rotate_left(a, b, result);
		} break;

		case EOperation_ChangeBase:
		{

		}

		default: 
		{
			status = EStatus_CalculationError;
		} break;
	}

	return status;
}

enum EStatus change_base(int a, enum EBase* base)
{
	if (base == NULL)
	{
		return EStatus_NullReferenceError;
	}

	enum EStatus status = EStatus_Success;

	switch(a)
	{
		case 1:
		{
			*base = EBase_Binary;
		} break;

		case 2:
		{
			*base = EBase_Octal;
		} break;

		case 3:
		{
			*base = EBase_Decimal;
		} break;

		case 4:
		{
			*base = EBase_Hexadecimal;
		} break;

		default: 
		{
			status = EStatus_CalculationError;
		} break;
	}

	return status;
}

#undef sizeof_inbits