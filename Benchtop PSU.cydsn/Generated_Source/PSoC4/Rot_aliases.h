/*******************************************************************************
* File Name: Rot.h  
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

#if !defined(CY_PINS_Rot_ALIASES_H) /* Pins Rot_ALIASES_H */
#define CY_PINS_Rot_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Rot_0			(Rot__0__PC)
#define Rot_0_PS		(Rot__0__PS)
#define Rot_0_PC		(Rot__0__PC)
#define Rot_0_DR		(Rot__0__DR)
#define Rot_0_SHIFT	(Rot__0__SHIFT)
#define Rot_0_INTR	((uint16)((uint16)0x0003u << (Rot__0__SHIFT*2u)))

#define Rot_1			(Rot__1__PC)
#define Rot_1_PS		(Rot__1__PS)
#define Rot_1_PC		(Rot__1__PC)
#define Rot_1_DR		(Rot__1__DR)
#define Rot_1_SHIFT	(Rot__1__SHIFT)
#define Rot_1_INTR	((uint16)((uint16)0x0003u << (Rot__1__SHIFT*2u)))

#define Rot_INTR_ALL	 ((uint16)(Rot_0_INTR| Rot_1_INTR))
#define Rot_A			(Rot__A__PC)
#define Rot_A_PS		(Rot__A__PS)
#define Rot_A_PC		(Rot__A__PC)
#define Rot_A_DR		(Rot__A__DR)
#define Rot_A_SHIFT	(Rot__A__SHIFT)
#define Rot_A_INTR	((uint16)((uint16)0x0003u << (Rot__0__SHIFT*2u)))

#define Rot_B			(Rot__B__PC)
#define Rot_B_PS		(Rot__B__PS)
#define Rot_B_PC		(Rot__B__PC)
#define Rot_B_DR		(Rot__B__DR)
#define Rot_B_SHIFT	(Rot__B__SHIFT)
#define Rot_B_INTR	((uint16)((uint16)0x0003u << (Rot__1__SHIFT*2u)))


#endif /* End Pins Rot_ALIASES_H */


/* [] END OF FILE */
