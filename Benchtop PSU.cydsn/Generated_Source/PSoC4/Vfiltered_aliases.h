/*******************************************************************************
* File Name: Vfiltered.h  
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

#if !defined(CY_PINS_Vfiltered_ALIASES_H) /* Pins Vfiltered_ALIASES_H */
#define CY_PINS_Vfiltered_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vfiltered_0			(Vfiltered__0__PC)
#define Vfiltered_0_PS		(Vfiltered__0__PS)
#define Vfiltered_0_PC		(Vfiltered__0__PC)
#define Vfiltered_0_DR		(Vfiltered__0__DR)
#define Vfiltered_0_SHIFT	(Vfiltered__0__SHIFT)
#define Vfiltered_0_INTR	((uint16)((uint16)0x0003u << (Vfiltered__0__SHIFT*2u)))

#define Vfiltered_INTR_ALL	 ((uint16)(Vfiltered_0_INTR))


#endif /* End Pins Vfiltered_ALIASES_H */


/* [] END OF FILE */
