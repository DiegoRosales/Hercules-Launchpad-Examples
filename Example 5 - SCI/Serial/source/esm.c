/** @file esm.c 
*   @brief Esm Driver Source File
*   @date 25.July.2013
*   @version 03.06.00
*
*   This file contains:
*   - API Functions
*   .
*   which are relevant for the Esm driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "esm.h"
#include "sys_vim.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void esmInit(void)
*   @brief Initializes Esm Driver
*
*   This function initializes the Esm driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void esmInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** - Disable error pin channels */
    esmREG->DEPAPR1 = 0xFFFFFFFFU;
    esmREG->IEPCR4 = 0xFFFFFFFFU;

    /** - Disable interrupts */
    esmREG->IECR1 = 0xFFFFFFFFU;
    esmREG->IECR4 = 0xFFFFFFFFU;

    /** - Clear error status flags */
    esmREG->SR1[0U] = 0xFFFFFFFFU;
    esmREG->SR1[1U] = 0xFFFFFFFFU;
    esmREG->SSR2  = 0xFFFFFFFFU;
    esmREG->SR1[2U] = 0xFFFFFFFFU;
    esmREG->SR4[0U] = 0xFFFFFFFFU;
    esmREG->SR4[1U] = 0xFFFFFFFFU;
    esmREG->ESTATUS5EMU  = 0xFFFFFFFFU;
    esmREG->SR4[2U] = 0xFFFFFFFFU;

    /** - Setup LPC preload */
    esmREG->LTCPR = 16384U - 1U;

    /** - Reset error pin */
    if (esmREG->EPSR == 0U)
    {
        esmREG->EKR = 0x00000005U;
    }
    else
    {
        esmREG->EKR = 0x00000000U;
    }

    /** - Clear interrupt level */
    esmREG->ILCR1 = 0xFFFFFFFFU;
    esmREG->ILCR4 = 0xFFFFFFFFU;

    /** - Set interrupt level */
    esmREG->ILSR1 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

    esmREG->ILSR4 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

    /** - Enable error pin channels */
    esmREG->EEPAPR1 = (0U << 31U)
                      | (0U << 30U)
                      | (0U << 29U)
                      | (0U << 28U)
                      | (0U << 27U)
                      | (0U << 26U)
                      | (0U << 25U)
                      | (0U << 24U)
                      | (0U << 23U)
                      | (0U << 22U)
                      | (0U << 21U)
                      | (0U << 20U)
                      | (0U << 19U)
                      | (0U << 18U)
                      | (0U << 17U)
                      | (0U << 16U)
                      | (0U << 15U)
                      | (0U << 14U)
                      | (0U << 13U)
                      | (0U << 12U)
                      | (0U << 11U)
                      | (0U << 10U)
                      | (0U <<  9U)
                      | (0U <<  8U)
                      | (0U <<  7U)
                      | (0U <<  6U)
                      | (0U <<  5U)
                      | (0U <<  4U)
                      | (0U <<  3U)
                      | (0U <<  2U)
                      | (0U <<  1U)
                      | (0U);

    esmREG->IEPSR4 = (0U << 31U)
                      | (0U << 30U)
                      | (0U << 29U)
                      | (0U << 28U)
                      | (0U << 27U)
                      | (0U << 26U)
                      | (0U << 25U)
                      | (0U << 24U)
                      | (0U << 23U)
                      | (0U << 22U)
                      | (0U << 21U)
                      | (0U << 20U)
                      | (0U << 19U)
                      | (0U << 18U)
                      | (0U << 17U)
                      | (0U << 16U)
                      | (0U << 15U)
                      | (0U << 14U)
                      | (0U << 13U)
                      | (0U << 12U)
                      | (0U << 11U)
                      | (0U << 10U)
                      | (0U <<  9U)
                      | (0U <<  8U)
                      | (0U <<  7U)
                      | (0U <<  6U)
                      | (0U <<  5U)
                      | (0U <<  4U)
                      | (0U <<  3U)
                      | (0U <<  2U)
                      | (0U <<  1U)
                      | (0U);

    /** - Enable interrupts */
    esmREG->IESR1 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

    esmREG->IESR4 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

/* USER CODE BEGIN (4) */
/* USER CODE END */
}


/** @fn uint32 esmError(void)
*   @brief Return Error status
*
*   @return The error status
*
*   Returns the error status.
*/
uint32 esmError(void)
{
    uint32 status;

/* USER CODE BEGIN (5) */
/* USER CODE END */

    status = esmREG->EPSR;

/* USER CODE BEGIN (6) */
/* USER CODE END */

    return status;
}


/** @fn void esmEnableError(uint64 channels)
*   @brief Enable Group 1 Channels Error Signals propagation
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmEnableError(uint64 channels)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

    esmREG->IEPSR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->EEPAPR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (8) */
/* USER CODE END */
}


/** @fn void esmDisableError(uint64 channels)
*   @brief Disable Group 1 Channels Error Signals propagation
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmDisableError(uint64 channels)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    esmREG->IEPCR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->DEPAPR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (10) */
/* USER CODE END */
}


/** @fn void esmTriggerErrorPinReset(void)
*   @brief Trigger error pin reset and switch back to normal operation
*
*   Trigger error pin reset and switch back to normal operation.
*/
void esmTriggerErrorPinReset(void)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    esmREG->EKR = 5U;

/* USER CODE BEGIN (12) */
/* USER CODE END */
}


/** @fn void esmActivateNormalOperation(void)
*   @brief Activate normal operation
*
*   Activates normal operation mode.
*/
void esmActivateNormalOperation(void)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    esmREG->EKR = 0U;

/* USER CODE BEGIN (14) */
/* USER CODE END */
}


/** @fn void esmEnableInterrupt(uint64 channels)
*   @brief Enable Group 1 Channels Interrupts
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Interrupts.
*/
void esmEnableInterrupt(uint64 channels)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    esmREG->IESR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->IESR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (16) */
/* USER CODE END */
}


/** @fn void esmDisableInterrupt(uint64 channels)
*   @brief Disable Group 1 Channels Interrupts
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Interrupts.
*/
void esmDisableInterrupt(uint64 channels)
{
/* USER CODE BEGIN (17) */
/* USER CODE END */

    esmREG->IECR4 = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->IECR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (18) */
/* USER CODE END */
}


/** @fn void esmSetInterruptLevel(uint64 channels, uint64 flags)
*   @brief Set Group 1 Channels Interrupt Levels
*
*   @param[in] channels - Channel mask
*   @param[in] flags - Level mask: - 0: Low priority interrupt
*                                  - 1: High priority interrupt
*
*   Set Group 1 Channels Interrupts levels.
*/
void esmSetInterruptLevel(uint64 channels, uint64 flags)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    esmREG->ILCR4 = (uint32)(((channels & (~flags)) >> 32U) & 0xFFFFFFFU);
    esmREG->ILSR4 = (uint32)(((channels & flags) >> 32U) & 0xFFFFFFFFU);
    esmREG->ILCR1 = (uint32)((channels & (~flags)) & 0xFFFFFFFU);
    esmREG->ILSR1 = (uint32)((channels & flags) & 0xFFFFFFFFU);

/* USER CODE BEGIN (20) */
/* USER CODE END */
}


/** @fn void esmClearStatus(uint32 group, uint64 channels)
*   @brief Clear Group error status
*
*   @param[in] group    - Error group
*   @param[in] channels - Channel mask
*
*   Clear Group error status.
*/
void esmClearStatus(uint32 group, uint64 channels)
{
/* USER CODE BEGIN (21) */
/* USER CODE END */

    esmREG->SR4[group] = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->SR1[group] = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (22) */
/* USER CODE END */
}


/** @fn void esmClearStatusBuffer(uint64 channels)
*   @brief Clear Group 2 error status buffer
*
*   @param[in] channels - Channel mask
*
*   Clear Group 2 error status buffer.
*/
void esmClearStatusBuffer(uint64 channels)
{
/* USER CODE BEGIN (23) */
/* USER CODE END */

    esmREG->ESTATUS5EMU = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->SSR2 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (24) */
/* USER CODE END */
}


/** @fn void esmSetCounterPreloadValue(uint32 value)
*   @brief Set counter preload value
*
*   @param[in] value - Counter preload value
*
*   Set counter preload value.
*/
void esmSetCounterPreloadValue(uint32 value)
{
/* USER CODE BEGIN (25) */
/* USER CODE END */

    esmREG->LTCPR = value & 0xC000U;

/* USER CODE BEGIN (26) */
/* USER CODE END */
}


/** @fn uint64 esmGetStatus(uint32 group, uint64 channels)
*   @brief Return Error status
*
*   @param[in] group   - Error group
*   @param[in] channels - Error Channels
*
*   @return The channels status of selected group
*
*   Returns the channels status of selected group.
*/
uint64 esmGetStatus(uint32 group, uint64 channels)
{
    uint64 status;
	uint32 ESM_ESTATUS4 = esmREG->SR4[group];
	uint32 ESM_ESTATUS1 = esmREG->SR1[group];

/* USER CODE BEGIN (27) */
/* USER CODE END */
    /*SAFETYMCUSW 51 S MR:12.3 <APPROVED> "Needs shifting for 64-bit value" */
    status = (((uint64)ESM_ESTATUS4 << 32U) | (uint64)ESM_ESTATUS1) & channels;

/* USER CODE BEGIN (28) */
/* USER CODE END */

    return status;
}


/** @fn uint64 esmGetStatusBuffer(uint64 channels)
*   @brief Return Group 2 channel x Error status buffer
*
*   @param[in] channels - Error Channels
*
*   @return The channels status
*
*   Returns the group 2 buffered status of selected channels.
*/
uint64 esmGetStatusBuffer(uint64 channels)
{
    uint64 status;
	uint32 ESM_ESTATUS5EMU = esmREG->ESTATUS5EMU;
	uint32 ESM_SSR2 = esmREG->SSR2;

/* USER CODE BEGIN (29) */
/* USER CODE END */
    /*SAFETYMCUSW 51 S MR:12.3 <APPROVED> "Needs shifting for 64-bit value" */
    status = (((uint64)ESM_ESTATUS5EMU << 32U) | (uint64)ESM_SSR2) & channels;

/* USER CODE BEGIN (30) */
/* USER CODE END */

    return status;
}

/** @fn esmSelfTestFlag_t esmEnterSelfTest(void)
*   @brief Return ESM Self test status
*
*   @return ESM Self test status
*
*   Returns the ESM Self test status.
*/
esmSelfTestFlag_t esmEnterSelfTest(void)
{
    esmSelfTestFlag_t status;

/* USER CODE BEGIN (31) */
/* USER CODE END */

	if(((esmREG->EPSR & 0x1U) == 0x0U) && (esmREG->EKR == 0x0U))
	{
	  status = esmSelfTest_NotStarted;
	}
	else
	{
	  esmREG->EKR = 0xAU;
	  status = esmSelfTest_Active;
	  if((esmREG->EPSR & 0x1U) != 0x0U)
	  {
	    status = esmSelfTest_Failed;
	  }
	  esmREG->EKR = 0x5U;
	}

/* USER CODE BEGIN (32) */
/* USER CODE END */

	return status;
}

/** @fn esmSelfTestFlag_t esmSelfTestStatus(void)
*   @brief Return ESM Self test status
*
*   Returns the ESM Self test status.
*/
esmSelfTestFlag_t esmSelfTestStatus(void)
{
    esmSelfTestFlag_t status;

/* USER CODE BEGIN (33) */
/* USER CODE END */

	if((esmREG->EPSR & 0x1U) == 0x0U) 
	{
	  if(esmREG->EKR == 0x5U)
	  { 
	    status = esmSelfTest_Active;
	  }
	  else
	  {
	    status = esmSelfTest_Failed;
	  }
	}
	else
	{
	    status = esmSelfTest_Passed;
	}

/* USER CODE BEGIN (34) */
/* USER CODE END */

	return status;
}

/** @fn void esmGetConfigValue(esm_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current 
*                           value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') 
*   of the configuration registers to the struct pointed by config_reg
*
*/

void esmGetConfigValue(esm_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_EEPAPR1 = ESM_EEPAPR1_CONFIGVALUE;
		config_reg->CONFIG_IESR1 = ESM_IESR1_CONFIGVALUE;
		config_reg->CONFIG_ILSR1 = ESM_ILSR1_CONFIGVALUE;
		config_reg->CONFIG_LTCPR = ESM_LTCPR_CONFIGVALUE;
		config_reg->CONFIG_EKR = ESM_EKR_CONFIGVALUE;  
		config_reg->CONFIG_IEPSR4 = ESM_IEPSR4_CONFIGVALUE;
		config_reg->CONFIG_IESR4 = ESM_IESR4_CONFIGVALUE;
		config_reg->CONFIG_ILSR4 = ESM_ILSR4_CONFIGVALUE;
	}
	else
	{
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
		config_reg->CONFIG_EEPAPR1 = esmREG->EEPAPR1;
		config_reg->CONFIG_IESR1 = esmREG->IESR1;
		config_reg->CONFIG_ILSR1 = esmREG->ILSR1;
		config_reg->CONFIG_LTCPR = esmREG->LTCPR;
		config_reg->CONFIG_EKR = esmREG->EKR;  
		config_reg->CONFIG_IEPSR4 = esmREG->IEPSR4;
		config_reg->CONFIG_IESR4 = esmREG->IESR4;
		config_reg->CONFIG_ILSR4 = esmREG->ILSR4;
	}
}

/* USER CODE BEGIN (35) */
/* USER CODE END */

/** @fn void esmHighInterrupt(void)
*   @brief High Level Interrupt for ESM
*/
#pragma CODE_STATE(esmHighInterrupt, 32)
#pragma INTERRUPT(esmHighInterrupt, FIQ)

void esmHighInterrupt(void)
{
    uint32 vec = esmREG->IOFFHR - 1U;

/* USER CODE BEGIN (36) */
/* USER CODE END */

    if (vec < 32U)
    {
        esmREG->SR1[0U] = 1U << vec;
        esmGroup1Notification(vec);
    }
    else if (vec < 64U)
    {
        esmREG->SR1[1U] = 1U << (vec-32U);
        esmGroup2Notification(vec-32U);
    }
    else if (vec < 96U)
    {
        esmREG->SR4[0U] = 1U << (vec-64U);
        esmGroup1Notification(vec-32U);
    }
    else if (vec < 128U)
    {
        esmREG->SR4[1U] = 1U << (vec-96U);
        esmGroup2Notification(vec-64U);
    }
    else
    {
        esmREG->SR4[1U] = 0xFFFFFFFFU;
        esmREG->SR4[0U] = 0xFFFFFFFFU;
        esmREG->SR1[1U] = 0xFFFFFFFFU;
        esmREG->SR1[0U] = 0xFFFFFFFFU;
    }

/* USER CODE BEGIN (37) */
/* USER CODE END */
}


/* USER CODE BEGIN (41) */
/* USER CODE END */
