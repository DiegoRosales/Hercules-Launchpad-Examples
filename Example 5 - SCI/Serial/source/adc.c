/** @file adc.c 
*   @brief ADC Driver Source File
*   @date 25.July.2013
*   @version 03.06.00
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the ADC driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "adc.h"
#include "sys_vim.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void adcInit(void)
*   @brief Initializes ADC Driver
*
*   This function initializes the ADC driver.
*
*/
/* USER CODE BEGIN (2) */
/* USER CODE END */
void adcInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** @b Initialize @b ADC1: */

    /** - Reset ADC module */
    adcREG1->RSTCR = 1U;
    adcREG1->RSTCR = 0U;

    /** - Enable 12-BIT ADC  */
    adcREG1->OPMODECR |= 0x80000000U;
	
    /** - Setup prescaler */
    adcREG1->CLOCKCR = 9U;
 
    /** - Setup memory boundaries */
    adcREG1->BNDCR  =(8U << 16U)|(8U + 8U);
    adcREG1->BNDEND = (adcREG1->BNDEND & 0xFFFF0000U) | (2U);
 
    /** - Setup event group conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[0U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup event group hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->EVSRC = 0x00000000U
                   | ADC1_EVENT;

    /** - Setup event group sample window */
    adcREG1->EVSAMP = 0U;

    /** - Setup event group sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->EVSAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Setup group 1 conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[1U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 1 hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->G1SRC = 0x00000000U
                   | ADC1_EVENT;

    /** - Setup group 1 sample window */
    adcREG1->G1SAMP = 0U;

    /** - Setup group 1 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G1SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Setup group 2 conversion mode
     *     - Setup data format
     *     - Enable/Disable channel id in conversion result
     *     - Enable/Disable continuous conversion
     */
    adcREG1->GxMODECR[2U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 2 hardware trigger
	*     - Setup hardware trigger edge
    *     - Setup hardware trigger source
	*/
    adcREG1->G2SRC = 0x00000000U
                   | ADC1_EVENT;

    /** - Setup group 2 sample window */
    adcREG1->G2SAMP = 0U;

    /** - Setup group 2 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G2SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Enable ADC module */
    adcREG1->OPMODECR |= 0x80140001U;

    /** - Wait for buffer initialization complete */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while (((adcREG1->BNDEND & 0xFFFF0000U) >> 16U ) != 0U) 
    { 
	} /* Wait */
    
    /** - Setup parity */
    adcREG1->PARCR = 0x00000005U;



/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @fn void adcStartConversion(adcBASE_t *adc, uint32 group)
*   @brief Starts an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function starts a conversion of the ADC hardware group.
*
*/

/** - s_adcSelect is used as constant table for channel selection */
static const uint32 s_adcSelect[1U][3U] =
{
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000040U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
   
};

/** - s_adcFiFoSize is used as constant table for channel selection */
static const uint32 s_adcFiFoSize[1U][3U] =
{
    16U,
    1U,
    16U,

};

/* USER CODE BEGIN (6) */
/* USER CODE END */

/** @fn void adcStartConversion(adcBASE_t *adc, uint32 group)
*   @brief Starts an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function starts a conversion of the ADC hardware group.
*
*/
void adcStartConversion(adcBASE_t *adc, uint32 group)
{

/* USER CODE BEGIN (7) */
/* USER CODE END */

    /** - Setup FiFo size */
    adc->GxINTCR[group] = s_adcFiFoSize[0][group];

    /** - Start Conversion */
    adc->GxSEL[group] = s_adcSelect[0][group];

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */


/** @fn void adcStopConversion(adcBASE_t *adc, uint32 group)
*   @brief Stops an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer

*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function stops a conversion of the ADC hardware group.
*
*/
void adcStopConversion(adcBASE_t *adc, uint32 group)
{
/* USER CODE BEGIN (10) */
/* USER CODE END */

    /** - Stop Conversion */
    adc->GxSEL[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (11) */
/* USER CODE END */
}

/* USER CODE BEGIN (12) */
/* USER CODE END */


/** @fn void adcResetFiFo(adcBASE_t *adc, uint32 group)
*   @brief Resets FiFo read and write pointer.
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function resets the FiFo read and write pointers.
*
*/
void adcResetFiFo(adcBASE_t *adc, uint32 group)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    /** - Reset FiFo */
    adc->GxFIFORESETCR[group] = 1U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           the conversion should be stopped before calling this function. 
    */

/* USER CODE BEGIN (14) */
/* USER CODE END */
}

/* USER CODE BEGIN (15) */
/* USER CODE END */


/** @fn uint32 adcGetData(adcBASE_t *adc, uint32 group, adcData_t *data)
*   @brief Gets converted a ADC values
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer

*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @param[out] data Pointer to store ADC converted data
*   @return The function will return the number of converted values copied into data buffer:
*
*   This function writes a ADC message into a ADC message box.
*
*/
uint32 adcGetData(adcBASE_t *adc, uint32 group, adcData_t *data)
{
    uint32       i;
    uint32  buf;
    uint32  mode;    
    uint32  count = (adc->GxINTCR[group] >= 256U) ? s_adcFiFoSize[0][group] : (s_adcFiFoSize[0][group] - (uint32)(adc->GxINTCR[group] & 0xFF));
    adcData_t *ptr = data; 

/* USER CODE BEGIN (16) */
/* USER CODE END */

    mode = ((adc->GxMODECR[group]) & 0x00000300U);

    if(mode == ADC_12_BIT)
      {
        /** -  Get conversion data and channel/pin id */
        for (i = 0U; i < count; i++)
        {
          buf        = adc->GxBUF[group].BUF0;
		  /*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
          ptr->value = (uint16)(buf & 0xFFFU);
          ptr->id    = (uint32)((buf >> 16U) & 0x1FU);
          ptr++;
        }
      }
      else
      {
        /** -  Get conversion data and channel/pin id */
        for (i = 0U; i < count; i++)
        {
          buf        = adc->GxBUF[group].BUF0;
		  /*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
          ptr->value = (uint16)(buf & 0x3FFU);
          ptr->id    = (uint32)((buf >> 10U) & 0x1FU);
          ptr++;
        }
      }


    adc->GxINTFLG[group] = 9U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           The user is responsible to initialize the message box.
    */

/* USER CODE BEGIN (17) */
/* USER CODE END */

    return count;
}

/* USER CODE BEGIN (18) */
/* USER CODE END */


/** @fn uint32 adcIsFifoFull(adcBASE_t *adc, uint32 group)
*   @brief Checks if FiFo buffer is full
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When FiFo buffer is not full   
*           - 1: When FiFo buffer is full   
*           - 3: When FiFo buffer overflow occured    
*
*   This function checks FiFo buffer status.
*
*/
uint32 adcIsFifoFull(adcBASE_t *adc, uint32 group)
{
    uint32 flags;

/* USER CODE BEGIN (19) */
/* USER CODE END */

    /** - Read FiFo flags */
    flags = adc->GxINTFLG[group] & 3U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (20) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (21) */
/* USER CODE END */


/** @fn uint32 adcIsConversionComplete(adcBASE_t *adc, uint32 group)
*   @brief Checks if Conversion is complete
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer

*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When is not finished   
*           - 8: When conversion is complete   
*
*   This function checks if conversion is complete.
*
*/
uint32 adcIsConversionComplete(adcBASE_t *adc, uint32 group)
{
    uint32 flags;

/* USER CODE BEGIN (22) */
/* USER CODE END */

    /** - Read conversion flags */
    flags = adc->GxINTFLG[group] & 8U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (23) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (24) */
/* USER CODE END */

/** @fn void adcCalibration(adcBASE_t *adc)
*   @brief Computes offset error using Calibration mode
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   This function computes offset error using Calibration mode
*
*/
void adcCalibration(adcBASE_t *adc)
{
/* USER CODE BEGIN (25) */
/* USER CODE END */
    
	uint32 conv_val[5U]={0U,0U,0U,0U,0U};
	uint32 loop_index=0U;
	uint32 offset_error=0U;
	uint32 backup_mode;
	
	/** - Backup Mode before Calibration  */
	backup_mode = adc->OPMODECR;
	
	/** - Enable 12-BIT ADC  */
	adcREG1->OPMODECR |= 0x80000000U;

	/* Disable all channels for conversion */
	adc->GxSEL[0]=0x00U;
	adc->GxSEL[1]=0x00U;
	adc->GxSEL[2]=0x00U;

	for(loop_index=0U;loop_index<4U;loop_index++)
	{
		/* Disable Self Test and Calibration mode */
		adc->CALCR=0x0U;
	
		switch(loop_index)
		{
			case 0U : 	/* Test 1 : Bride En = 0 , HiLo =0 */
						adc->CALCR=0x0U;
						break;

			case 1U :	/* Test 1 : Bride En = 0 , HiLo =1 */
						adc->CALCR=0x0100U;
						break;

			case 2U : 	/* Test 1 : Bride En = 1 , HiLo =0 */
						adc->CALCR=0x0200U;
						break;
		
			case 3U : 	/* Test 1 : Bride En = 1 , HiLo =1 */
						adc->CALCR=0x0300U;
						break;
			default :
			            break;
		}
	
		/* Enable Calibration mode */
		adc->CALCR|=0x1U;
	
		/* Start calibration conversion */
		adc->CALCR|=0x00010000U;

		/* Wait for calibration conversion to complete */
		/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
		while((adc->CALCR & 0x00010000U)==0x00010000U)
	    { 
	    } /* Wait */

		/* Read converted value */
		conv_val[loop_index]= adc->CALR;
	}

	/* Disable Self Test and Calibration mode */
	adc->CALCR=0x0U;

	/* Compute the Offset error correction value */
	conv_val[4]=conv_val[0]+ conv_val[1] + conv_val[2] + conv_val[3];

	conv_val[4]=(conv_val[4]/4);

	offset_error=conv_val[4]-0x7FFU;

	/*Write the offset error to the Calibration register */
	/* Load 2;s complement of the computed value to ADCALR register */
	offset_error=~offset_error;
	offset_error=offset_error & 0xFFFU;
	offset_error=offset_error+1U;

	adc->CALR = offset_error;

  /** - Restore Mode after Calibration  */
	adc->OPMODECR = backup_mode;
	
 /**   @note The function adcInit has to be called before using this function. */

/* USER CODE BEGIN (26) */
/* USER CODE END */
}


/** @fn void adcMidPointCalibration(adcBASE_t *adc)
*   @brief Computes offset error using Mid Point Calibration mode
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   This function computes offset error using Mid Point Calibration mode
*
*/
uint32 adcMidPointCalibration(adcBASE_t *adc)
{
/* USER CODE BEGIN (27) */
/* USER CODE END */
    
	uint32 conv_val[3]={0,0,0};
	uint32 loop_index=0U;
	uint32 offset_error=0U;
	uint32 backup_mode;
	
	/** - Backup Mode before Calibration  */
	backup_mode = adc->OPMODECR;
	
	/** - Enable 12-BIT ADC  */
	adcREG1->OPMODECR |= 0x80000000U;

	/* Disable all channels for conversion */
	adc->GxSEL[0]=0x00U;
	adc->GxSEL[1]=0x00U;
	adc->GxSEL[2]=0x00U;

	for(loop_index=0U;loop_index<2U;loop_index++)
	{
		/* Disable Self Test and Calibration mode */
		adc->CALCR=0x0U;
	
		switch(loop_index)
		{
			case 0U : 	/* Test 1 : Bride En = 0 , HiLo =0 */
						adc->CALCR=0x0U;
						break;

			case 1U :	/* Test 1 : Bride En = 0 , HiLo =1 */
						adc->CALCR=0x0100U;
						break;

			default :
			            break;						

		}
	
		/* Enable Calibration mode */
		adc->CALCR|=0x1U;
	
		/* Start calibration conversion */
		adc->CALCR|=0x00010000U;

		/* Wait for calibration conversion to complete */
		/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
		while((adc->CALCR & 0x00010000U)==0x00010000U)
	    { 
	    } /* Wait */

		/* Read converted value */
		conv_val[loop_index]= adc->CALR;
	}

	/* Disable Self Test and Calibration mode */
	adc->CALCR=0x0U;

	/* Compute the Offset error correction value */
	conv_val[2]=(conv_val[0])+ (conv_val[1]);

	conv_val[2]=(conv_val[2]/2);

	offset_error=conv_val[2]-0x7FFU;

	/* Write the offset error to the Calibration register           */
	/* Load 2's complement of the computed value to ADCALR register */
	offset_error=~offset_error;
	offset_error=offset_error & 0xFFFU;
	offset_error=offset_error+1U;

	adc->CALR = offset_error;

  /** - Restore Mode after Calibration  */
	adc->OPMODECR = backup_mode;
	
	return(offset_error);

 /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (28) */
/* USER CODE END */
}

/* USER CODE BEGIN (29) */
/* USER CODE END */

/** @fn void adcEnableNotification(adcBASE_t *adc, uint32 group)
*   @brief Enable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will enable the notification of a conversion.
*   In single conversion mode for conversion complete and
*   in continuous conversion mode when the FiFo buffer is full.
*
*/
void adcEnableNotification(adcBASE_t *adc, uint32 group)
{
    uint32 notif = (((uint32)(adc->GxMODECR[group]) & 2U) == 2U) ? 1U : 8U;

/* USER CODE BEGIN (30) */
/* USER CODE END */

    adc->GxINTENA[group] = notif;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           This function should be called before the conversion is started
    */

/* USER CODE BEGIN (31) */
/* USER CODE END */
}

/* USER CODE BEGIN (32) */
/* USER CODE END */


/** @fn void adcDisableNotification(adcBASE_t *adc, uint32 group)
*   @brief Disable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will disable the notification of a conversion.
*/
void adcDisableNotification(adcBASE_t *adc, uint32 group)
{
/* USER CODE BEGIN (33) */
/* USER CODE END */

    adc->GxINTENA[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (34) */
/* USER CODE END */
}

/** @fn void adc1GetConfigValue(adc_config_reg_t *config_reg, config_value_type_t type)
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
void adc1GetConfigValue(adc_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
        config_reg->CONFIG_OPMODECR = ADC1_OPMODECR_CONFIGVALUE;
        config_reg->CONFIG_CLOCKCR = ADC1_CLOCKCR_CONFIGVALUE;
        config_reg->CONFIG_GxMODECR[0U] = ADC1_G0MODECR_CONFIGVALUE;
        config_reg->CONFIG_GxMODECR[1U] = ADC1_G1MODECR_CONFIGVALUE;
        config_reg->CONFIG_GxMODECR[2U] = ADC1_G2MODECR_CONFIGVALUE;
        config_reg->CONFIG_G0SRC = ADC1_G0SRC_CONFIGVALUE;
        config_reg->CONFIG_G1SRC = ADC1_G1SRC_CONFIGVALUE;
        config_reg->CONFIG_G2SRC = ADC1_G2SRC_CONFIGVALUE;
        config_reg->CONFIG_BNDCR = ADC1_BNDCR_CONFIGVALUE;
        config_reg->CONFIG_BNDEND = ADC1_BNDEND_CONFIGVALUE;
        config_reg->CONFIG_G0SAMP = ADC1_G0SAMP_CONFIGVALUE;
        config_reg->CONFIG_G1SAMP = ADC1_G1SAMP_CONFIGVALUE;
        config_reg->CONFIG_G2SAMP = ADC1_G2SAMP_CONFIGVALUE;
        config_reg->CONFIG_G0SAMPDISEN = ADC1_G0SAMPDISEN_CONFIGVALUE;
        config_reg->CONFIG_G1SAMPDISEN = ADC1_G1SAMPDISEN_CONFIGVALUE;
        config_reg->CONFIG_G2SAMPDISEN = ADC1_G2SAMPDISEN_CONFIGVALUE;
        config_reg->CONFIG_PARCR = ADC1_PARCR_CONFIGVALUE;
	}
	else
	{
        config_reg->CONFIG_OPMODECR = adcREG1->OPMODECR;
        config_reg->CONFIG_CLOCKCR = adcREG1->CLOCKCR;
        config_reg->CONFIG_GxMODECR[0U] = adcREG1->GxMODECR[0U];
        config_reg->CONFIG_GxMODECR[1U] = adcREG1->GxMODECR[1U];
        config_reg->CONFIG_GxMODECR[2U] = adcREG1->GxMODECR[2U];
        config_reg->CONFIG_G0SRC = adcREG1->EVSRC;
        config_reg->CONFIG_G1SRC = adcREG1->G1SRC;
        config_reg->CONFIG_G2SRC = adcREG1->G2SRC;
        config_reg->CONFIG_BNDCR = adcREG1->BNDCR;
        config_reg->CONFIG_BNDEND = adcREG1->BNDEND;
        config_reg->CONFIG_G0SAMP = adcREG1->EVSAMP;
        config_reg->CONFIG_G1SAMP = adcREG1->G1SAMP;
        config_reg->CONFIG_G2SAMP = adcREG1->G2SAMP;
        config_reg->CONFIG_G0SAMPDISEN = adcREG1->EVSAMPDISEN;
        config_reg->CONFIG_G1SAMPDISEN = adcREG1->G1SAMPDISEN;
        config_reg->CONFIG_G2SAMPDISEN = adcREG1->G2SAMPDISEN;
        config_reg->CONFIG_PARCR = adcREG1->PARCR;
	}
}
/* USER CODE BEGIN (35) */
/* USER CODE END */




/* USER CODE BEGIN (44) */
/* USER CODE END */