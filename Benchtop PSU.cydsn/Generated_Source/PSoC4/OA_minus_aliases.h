/*******************************************************************************
* File Name: OA_minus.h  
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

#if !defined(CY_PINS_OA_minus_ALIASES_H) /* Pins OA_minus_ALIASES_H */
#define CY_PINS_OA_minus_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define OA_minus_0			(OA_minus__0__PC)
#define OA_minus_0_PS		(OA_minus__0__PS)
#define OA_minus_0_PC		(OA_minus__0__PC)
#define OA_minus_0_DR		(OA_minus__0__DR)
#define OA_minus_0_SHIFT	(OA_minus__0__SHIFT)
#define OA_minus_0_INTR	((uint16)((uint16)0x0003u << (OA_minus__0__SHIFT*2u)))

#define OA_minus_INTR_ALL	 ((uint16)(OA_minus_0_INTR))


#endif /* End Pins OA_minus_ALIASES_H */


/* [] END OF FILE */
