/*******************************************************************************
* File Name: Vpos.h  
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

#if !defined(CY_PINS_Vpos_ALIASES_H) /* Pins Vpos_ALIASES_H */
#define CY_PINS_Vpos_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vpos_0			(Vpos__0__PC)
#define Vpos_0_PS		(Vpos__0__PS)
#define Vpos_0_PC		(Vpos__0__PC)
#define Vpos_0_DR		(Vpos__0__DR)
#define Vpos_0_SHIFT	(Vpos__0__SHIFT)
#define Vpos_0_INTR	((uint16)((uint16)0x0003u << (Vpos__0__SHIFT*2u)))

#define Vpos_INTR_ALL	 ((uint16)(Vpos_0_INTR))


#endif /* End Pins Vpos_ALIASES_H */


/* [] END OF FILE */
