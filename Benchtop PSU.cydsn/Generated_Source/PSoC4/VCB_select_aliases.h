/*******************************************************************************
* File Name: VCB_select.h  
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

#if !defined(CY_PINS_VCB_select_ALIASES_H) /* Pins VCB_select_ALIASES_H */
#define CY_PINS_VCB_select_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VCB_select_0			(VCB_select__0__PC)
#define VCB_select_0_PS		(VCB_select__0__PS)
#define VCB_select_0_PC		(VCB_select__0__PC)
#define VCB_select_0_DR		(VCB_select__0__DR)
#define VCB_select_0_SHIFT	(VCB_select__0__SHIFT)
#define VCB_select_0_INTR	((uint16)((uint16)0x0003u << (VCB_select__0__SHIFT*2u)))

#define VCB_select_INTR_ALL	 ((uint16)(VCB_select_0_INTR))


#endif /* End Pins VCB_select_ALIASES_H */


/* [] END OF FILE */
