/*******************************************************************************
* File Name: PINH.h  
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

#if !defined(CY_PINS_PINH_ALIASES_H) /* Pins PINH_ALIASES_H */
#define CY_PINS_PINH_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PINH_0			(PINH__0__PC)
#define PINH_0_PS		(PINH__0__PS)
#define PINH_0_PC		(PINH__0__PC)
#define PINH_0_DR		(PINH__0__DR)
#define PINH_0_SHIFT	(PINH__0__SHIFT)
#define PINH_0_INTR	((uint16)((uint16)0x0003u << (PINH__0__SHIFT*2u)))

#define PINH_INTR_ALL	 ((uint16)(PINH_0_INTR))


#endif /* End Pins PINH_ALIASES_H */


/* [] END OF FILE */
