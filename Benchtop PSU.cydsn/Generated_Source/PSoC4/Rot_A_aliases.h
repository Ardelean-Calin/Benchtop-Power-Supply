/*******************************************************************************
* File Name: Rot_A.h  
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

#if !defined(CY_PINS_Rot_A_ALIASES_H) /* Pins Rot_A_ALIASES_H */
#define CY_PINS_Rot_A_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Rot_A_0			(Rot_A__0__PC)
#define Rot_A_0_PS		(Rot_A__0__PS)
#define Rot_A_0_PC		(Rot_A__0__PC)
#define Rot_A_0_DR		(Rot_A__0__DR)
#define Rot_A_0_SHIFT	(Rot_A__0__SHIFT)
#define Rot_A_0_INTR	((uint16)((uint16)0x0003u << (Rot_A__0__SHIFT*2u)))

#define Rot_A_INTR_ALL	 ((uint16)(Rot_A_0_INTR))


#endif /* End Pins Rot_A_ALIASES_H */


/* [] END OF FILE */
