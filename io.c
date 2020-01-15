#include "io.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 50

enum EStatus get_op(enum EOperation* op)
{	
	enum EOperation temp;

	if (op == NULL)
	{
		return EStatus_NullReferenceError;
	}

	puts("Which operation would you like to take?\n");
	for (int i = (int)EOperation_FirstOperation; i < EOperation_NumOfOperations; i++)
	{
		printf("%i. %s\n", i, EOperation_ToString[i]);
	}

	char str[STRING_SIZE];
	memset(str, '\0', sizeof(str));

	char *s = fgets(str, STRING_SIZE-1, stdin);

	if (s == NULL)
	{
		return EStatus_IOError;
	}

	if (!isinteger(str, EBase_Decimal))
	{
		return EStatus_BadOpInput;
	}

	temp = atoi(str);

	if (!(EOperation_FirstOperation <= temp && temp < EOperation_NumOfOperations))
	{
		return EStatus_BadOpInput;
	}

	*op = temp;

	return EStatus_Success;
}

enum EStatus get_number(int* x, enum EBase base)
{
	if (x == NULL)
	{
		return EStatus_NullReferenceError;
	}

	char str[STRING_SIZE];
	memset(str, '\0', sizeof(str));

	char *s = fgets(str, STRING_SIZE-1, stdin);

	if (s == NULL)
	{
		return EStatus_IOError;
	}

	if (!isinteger(str, base))
	{
		return EStatus_BadInput;
	}

	*x = strtol(str, NULL, base);

	return EStatus_Success;
}

enum EStatus get_input(int* a, int* b, enum EOperation op, enum EBase base)
{
	if (a == NULL || b == NULL)
	{
		return EStatus_NullReferenceError;
	}

	enum EStatus err;

	if(operationUsesTwoOperands(op))
	{
		printf("Enter the first number: ");

		err = get_number(a, base);

		if (err != EStatus_Success)
		{
			return err;
		}

		printf("Enter the second number: ");

		err = get_number(b, base);

		if (err != EStatus_Success)
		{
			return err;
		}
	}
	else if (op == EOperation_ChangeBase)
	{
		puts("Which base do you want to switch to?\n");
		puts("1. Binary");
		puts("2. Octal");
		puts("3. Decimal");
		puts("4. Hexadecimal");

		err = get_number(a, EBase_Decimal);

		if (err != EStatus_Success)
		{
			return err;
		}

		if (a < 1 && 4 < a)
		{
			return EStatus_BadBaseInput;
		}
	}
	else if (operationUsesOneOperand(op))
	{
		printf("Enter a number: ");

		err = get_number(a, base);

		if (err != EStatus_Success)
		{
			return err;
		}
	}
	else
	{
		return EStatus_OperationNotValid;
	}
	return EStatus_Success;
}

#undef STRING_SIZE