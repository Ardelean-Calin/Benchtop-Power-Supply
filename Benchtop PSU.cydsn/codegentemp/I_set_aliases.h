/*******************************************************************************
* File Name: I_set.h  
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

#if !defined(CY_PINS_I_set_ALIASES_H) /* Pins I_set_ALIASES_H */
#define CY_PINS_I_set_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define I_set_0			(I_set__0__PC)
#define I_set_0_PS		(I_set__0__PS)
#define I_set_0_PC		(I_set__0__PC)
#define I_set_0_DR		(I_set__0__DR)
#define I_set_0_SHIFT	(I_set__0__SHIFT)
#define I_set_0_INTR	((uint16)((uint16)0x0003u << (I_set__0__SHIFT*2u)))

#define I_set_INTR_ALL	 ((uint16)(I_set_0_INTR))


#endif /* End Pins I_set_ALIASES_H */


/* [] END OF FILE */
