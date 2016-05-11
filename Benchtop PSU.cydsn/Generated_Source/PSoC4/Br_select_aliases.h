/*******************************************************************************
* File Name: Br_select.h  
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

#if !defined(CY_PINS_Br_select_ALIASES_H) /* Pins Br_select_ALIASES_H */
#define CY_PINS_Br_select_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Br_select_0			(Br_select__0__PC)
#define Br_select_0_PS		(Br_select__0__PS)
#define Br_select_0_PC		(Br_select__0__PC)
#define Br_select_0_DR		(Br_select__0__DR)
#define Br_select_0_SHIFT	(Br_select__0__SHIFT)
#define Br_select_0_INTR	((uint16)((uint16)0x0003u << (Br_select__0__SHIFT*2u)))

#define Br_select_INTR_ALL	 ((uint16)(Br_select_0_INTR))


#endif /* End Pins Br_select_ALIASES_H */


/* [] END OF FILE */
