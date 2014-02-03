/*******************************************************
 * Created by Diego Rosales using HALcoGen Templates
 *
 * This is the first part on how to make use of the FTDI
 * chip on the board to achieve serial communications
 * using the SCI module
 * 
 * For more info go to
 * http://produccionyelectronica.blogspot.com/
 *
 * Created on January 1 / 2013
 *******************************************************/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
#include "sci.h"
#include "adc.h"
#include "stdlib.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
unsigned char command[8];
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
unsigned char mensaje[4];
unsigned char comp[4] = "1234";
unsigned char *dir_mensaje = mensaje;

bool comparacion(unsigned char a[], unsigned char b[])
{
	int i=0;
	bool x;
	if(sizeof(a) != sizeof(b))
	{
		x=false;
	}
	else
	{
		while(i<sizeof(a))
		{
			if (a[i] == b[i])
			{
				x=true;
			}
			else
			{
				i=sizeof(a);
				x=false;
			}
			i++;
		}
	}

	return x;
}
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	sciInit();
	adcInit();
	unsigned char mensaje2[] = "Mensaje de prueba \n\r";

	while(1)
	{
		sciSend(scilinREG, sizeof(mensaje2)-1, (unsigned char *)&mensaje2);
	}
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
