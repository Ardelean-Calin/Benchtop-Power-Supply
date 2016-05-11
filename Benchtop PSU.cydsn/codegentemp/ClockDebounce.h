/*******************************************************************************
* File Name: ClockDebounce.h
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

#if !defined(CY_CLOCK_ClockDebounce_H)
#define CY_CLOCK_ClockDebounce_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ClockDebounce_StartEx(uint32 alignClkDiv);
#define ClockDebounce_Start() \
    ClockDebounce_StartEx(ClockDebounce__PA_DIV_ID)

#else

void ClockDebounce_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ClockDebounce_Stop(void);

void ClockDebounce_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ClockDebounce_GetDividerRegister(void);
uint8  ClockDebounce_GetFractionalDividerRegister(void);

#define ClockDebounce_Enable()                         ClockDebounce_Start()
#define ClockDebounce_Disable()                        ClockDebounce_Stop()
#define ClockDebounce_SetDividerRegister(clkDivider, reset)  \
    ClockDebounce_SetFractionalDividerRegister((clkDivider), 0u)
#define ClockDebounce_SetDivider(clkDivider)           ClockDebounce_SetDividerRegister((clkDivider), 1u)
#define ClockDebounce_SetDividerValue(clkDivider)      ClockDebounce_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ClockDebounce_DIV_ID     ClockDebounce__DIV_ID

#define ClockDebounce_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ClockDebounce_CTRL_REG   (*(reg32 *)ClockDebounce__CTRL_REGISTER)
#define ClockDebounce_DIV_REG    (*(reg32 *)ClockDebounce__DIV_REGISTER)

#define ClockDebounce_CMD_DIV_SHIFT          (0u)
#define ClockDebounce_CMD_PA_DIV_SHIFT       (8u)
#define ClockDebounce_CMD_DISABLE_SHIFT      (30u)
#define ClockDebounce_CMD_ENABLE_SHIFT       (31u)

#define ClockDebounce_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ClockDebounce_CMD_DISABLE_SHIFT))
#define ClockDebounce_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ClockDebounce_CMD_ENABLE_SHIFT))

#define ClockDebounce_DIV_FRAC_MASK  (0x000000F8u)
#define ClockDebounce_DIV_FRAC_SHIFT (3u)
#define ClockDebounce_DIV_INT_MASK   (0xFFFFFF00u)
#define ClockDebounce_DIV_INT_SHIFT  (8u)

#else 

#define ClockDebounce_DIV_REG        (*(reg32 *)ClockDebounce__REGISTER)
#define ClockDebounce_ENABLE_REG     ClockDebounce_DIV_REG
#define ClockDebounce_DIV_FRAC_MASK  ClockDebounce__FRAC_MASK
#define ClockDebounce_DIV_FRAC_SHIFT (16u)
#define ClockDebounce_DIV_INT_MASK   ClockDebounce__DIVIDER_MASK
#define ClockDebounce_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ClockDebounce_H) */

/* [] END OF FILE */
