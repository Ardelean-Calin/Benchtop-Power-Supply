/*******************************************************************************
* File Name: HFCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_HFCLK_H)
#define CY_CLOCK_HFCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void HFCLK_StartEx(uint32 alignClkDiv);
#define HFCLK_Start() \
    HFCLK_StartEx(HFCLK__PA_DIV_ID)

#else

void HFCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void HFCLK_Stop(void);

void HFCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 HFCLK_GetDividerRegister(void);
uint8  HFCLK_GetFractionalDividerRegister(void);

#define HFCLK_Enable()                         HFCLK_Start()
#define HFCLK_Disable()                        HFCLK_Stop()
#define HFCLK_SetDividerRegister(clkDivider, reset)  \
    HFCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define HFCLK_SetDivider(clkDivider)           HFCLK_SetDividerRegister((clkDivider), 1u)
#define HFCLK_SetDividerValue(clkDivider)      HFCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define HFCLK_DIV_ID     HFCLK__DIV_ID

#define HFCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define HFCLK_CTRL_REG   (*(reg32 *)HFCLK__CTRL_REGISTER)
#define HFCLK_DIV_REG    (*(reg32 *)HFCLK__DIV_REGISTER)

#define HFCLK_CMD_DIV_SHIFT          (0u)
#define HFCLK_CMD_PA_DIV_SHIFT       (8u)
#define HFCLK_CMD_DISABLE_SHIFT      (30u)
#define HFCLK_CMD_ENABLE_SHIFT       (31u)

#define HFCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << HFCLK_CMD_DISABLE_SHIFT))
#define HFCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << HFCLK_CMD_ENABLE_SHIFT))

#define HFCLK_DIV_FRAC_MASK  (0x000000F8u)
#define HFCLK_DIV_FRAC_SHIFT (3u)
#define HFCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define HFCLK_DIV_INT_SHIFT  (8u)

#else 

#define HFCLK_DIV_REG        (*(reg32 *)HFCLK__REGISTER)
#define HFCLK_ENABLE_REG     HFCLK_DIV_REG
#define HFCLK_DIV_FRAC_MASK  HFCLK__FRAC_MASK
#define HFCLK_DIV_FRAC_SHIFT (16u)
#define HFCLK_DIV_INT_MASK   HFCLK__DIVIDER_MASK
#define HFCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_HFCLK_H) */

/* [] END OF FILE */
