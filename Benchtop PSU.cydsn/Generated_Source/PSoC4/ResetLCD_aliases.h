/*******************************************************************************
* File Name: ResetLCD.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ResetLCD_ALIASES_H) /* Pins ResetLCD_ALIASES_H */
#define CY_PINS_ResetLCD_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ResetLCD_0			(ResetLCD__0__PC)
#define ResetLCD_0_PS		(ResetLCD__0__PS)
#define ResetLCD_0_PC		(ResetLCD__0__PC)
#define ResetLCD_0_DR		(ResetLCD__0__DR)
#define ResetLCD_0_SHIFT	(ResetLCD__0__SHIFT)
#define ResetLCD_0_INTR	((uint16)((uint16)0x0003u << (ResetLCD__0__SHIFT*2u)))

#define ResetLCD_INTR_ALL	 ((uint16)(ResetLCD_0_INTR))


#endif /* End Pins ResetLCD_ALIASES_H */


/* [] END OF FILE */
