#include <stdio.h>
#include <stdlib.h>

#include "calculation.h"
#include "io.h"
#include "utilities.h"

int main(int argc, char *argv[]) 
{	
	int a; // first number to do calculation on
	int b; // second number to do calculation on
	int res; // the result of the calculation
	char* res_str = NULL;
	enum EStatus err; // errror value
	enum EOperation operation; // the operation to do  on variables a and b
	enum EBase base = EBase_Decimal; // which base the input and output will be

	while(1)
	{
		err = get_op(&operation); 
	
		if(err != EStatus_Success)
		{
			handle_error(err);
			goto EndOfCalculation;
		}

		if(operation == EOperation_ExitProgram)
		{
			break;
		}

		err = get_input(&a, &b, operation, base);

		if(err != EStatus_Success)
		{
			handle_error(err);
			goto EndOfCalculation;
		}

		if (operation == EOperation_ChangeBase)
		{
			err = change_base(a, &base);

			if(err != EStatus_Success)
			{
				handle_error(err);
			}
			
			goto EndOfCalculation;
		}

		err = calculate_result(a, b, operation, &res);

		if (err == EStatus_Overflow)
		{
			printf("An overflow happend during the calculation\n");
		}
		else if(err != EStatus_Success)
		{
			handle_error(err);
			goto EndOfCalculation;
		}

		res_str = int_to_base_string(res, base);

		printf("the result of this calculation is: %s\n", res_str);

		if (res_str != NULL)
		{
			free(res_str);
		}

		EndOfCalculation:;
	}

	return 0;
}