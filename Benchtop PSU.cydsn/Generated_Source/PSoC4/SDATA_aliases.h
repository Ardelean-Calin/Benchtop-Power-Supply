/*******************************************************************************
* File Name: SDATA.h  
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

#if !defined(CY_PINS_SDATA_ALIASES_H) /* Pins SDATA_ALIASES_H */
#define CY_PINS_SDATA_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SDATA_0			(SDATA__0__PC)
#define SDATA_0_PS		(SDATA__0__PS)
#define SDATA_0_PC		(SDATA__0__PC)
#define SDATA_0_DR		(SDATA__0__DR)
#define SDATA_0_SHIFT	(SDATA__0__SHIFT)
#define SDATA_0_INTR	((uint16)((uint16)0x0003u << (SDATA__0__SHIFT*2u)))

#define SDATA_INTR_ALL	 ((uint16)(SDATA_0_INTR))


#endif /* End Pins SDATA_ALIASES_H */


/* [] END OF FILE */
