/*******************************************************
 * Created by Diego Rosales using HALcoGen Templates
 *
 * This is the second part on how to use basic Interrupt functionalities
 * 
 * For more info go to
 * http://produccionyelectronica.blogspot.com/
 *
 * Created on December 22 / 2013
 *******************************************************/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
#include "rti.h"
#include "gio.h"
#include "het.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	// Inicializa los módulos
	gioInit();
	hetInit();
	rtiInit();

	// Habilita las interrupciones
	rtiEnableNotification(rtiNOTIFICATION_COMPARE0);
	_enable_IRQ();

	// Inicia el contador del módulo RTI
	rtiStartCounter(rtiCOUNTER_BLOCK0);

	// Ciclo infinito
	while(1);
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
