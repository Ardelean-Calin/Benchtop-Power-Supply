/*******************************************************************************
* File Name: An_v.h  
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

#if !defined(CY_PINS_An_v_ALIASES_H) /* Pins An_v_ALIASES_H */
#define CY_PINS_An_v_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define An_v_0			(An_v__0__PC)
#define An_v_0_PS		(An_v__0__PS)
#define An_v_0_PC		(An_v__0__PC)
#define An_v_0_DR		(An_v__0__DR)
#define An_v_0_SHIFT	(An_v__0__SHIFT)
#define An_v_0_INTR	((uint16)((uint16)0x0003u << (An_v__0__SHIFT*2u)))

#define An_v_INTR_ALL	 ((uint16)(An_v_0_INTR))


#endif /* End Pins An_v_ALIASES_H */


/* [] END OF FILE */
