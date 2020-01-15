#include "utilities.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* EStatus_ToString[] = 
{
	"Success",
	"General error",
	"Calculation error",
	"Overflow", 
	"Divide by zero",
	"IO error",
	"Bad input error: the input should be an integer number",
	"Bad operation input errror: the operation inputted should be from numbers 1-11",
	"Bad base input errror: the base inputted should be from numbers 1-4",
	"Null reference error",
	"Operation not valid error"
};

int ischarinbase(char c, enum EBase base) 
{
	switch(base)
	{
		case EBase_Binary: 
		{
			if(c == '0' || c == '1')
			{
				return 1;
			}
		} break;

		case EBase_Octal:
		{
			if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7')
			{
				return 1;
			}
		} break;

		case EBase_Decimal:
		{
			if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
			{
				 return 1;
			}
		} break;

		case EBase_Hexadecimal:
		{
			if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == 'a' || c == 'A' || c == 'b' || c == 'B' || c == 'c' || c == 'C' || c == 'd' || c == 'D' || c == 'e' || c == 'E' || c == 'f' || c == 'F')
			{
				 return 1;
			}
		} break;

		default:
		{
			break;
		}
	}
	return 0;
}

int isinteger(char* s, enum EBase base)
{
	int i = 0; //index
	while(s[i] != '\0' && s[i] != '\n')
	{
		if(i == 0 && base == EBase_Decimal)
		{
			if(!ischarinbase(s[i], base) && s[i] != '-')
			{
				return 0;
			}
		}
		else
		{
			if(!ischarinbase(s[i], base)) 
			{
				return 0;
			}
		}

		i++;
	}
	return 1;
}

// on error return 0
char int_to_char(int a) 
{
	if (0 <= a && a <= 9)
	{
		return a + '0';
	}
	else if (10 <= a && a <= 15)
	{
		return a - 10 + 'a';
	}
	return 0;
}

char* int_to_base_string(int a, enum EBase base)
{
	char* str_temp = malloc(sizeof_inbits(int) + 1);
	memset(str_temp, '\0', sizeof_inbits(int) + 1);
	char* str = malloc(sizeof_inbits(int) + 1);
	memset(str, '\0', sizeof_inbits(int) + 1);

	int i = 0;

	while(a != 0)
	{
		str_temp[i] = int_to_char(a % base);
		a = a / base;
		i++;
	}
	
	i = 0;
	
	size_t len = strlen(str_temp);

	while(str_temp[i] != '\0')
	{
		str[len - i - 1] = str_temp[i];
		i++;
	}

	free(str_temp);

	return str;
}

int handle_error(enum EStatus s)
{
	char* err_string = (EStatus_Success <= s && s < EStatus_NumOfErrors) ? EStatus_ToString[s] : "Unkown error";

	printf("Error accured:\nError value: %i\n%s\n", s, err_string);

	return 0;
}