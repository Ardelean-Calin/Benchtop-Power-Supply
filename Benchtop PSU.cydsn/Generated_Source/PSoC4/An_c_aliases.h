/*******************************************************************************
* File Name: An_c.h  
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

#if !defined(CY_PINS_An_c_ALIASES_H) /* Pins An_c_ALIASES_H */
#define CY_PINS_An_c_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define An_c_0			(An_c__0__PC)
#define An_c_0_PS		(An_c__0__PS)
#define An_c_0_PC		(An_c__0__PC)
#define An_c_0_DR		(An_c__0__DR)
#define An_c_0_SHIFT	(An_c__0__SHIFT)
#define An_c_0_INTR	((uint16)((uint16)0x0003u << (An_c__0__SHIFT*2u)))

#define An_c_INTR_ALL	 ((uint16)(An_c_0_INTR))


#endif /* End Pins An_c_ALIASES_H */


/* [] END OF FILE */
