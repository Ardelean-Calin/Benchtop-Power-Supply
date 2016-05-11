/*******************************************************************************
* File Name: ClockPWM.h
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

#if !defined(CY_CLOCK_ClockPWM_H)
#define CY_CLOCK_ClockPWM_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ClockPWM_StartEx(uint32 alignClkDiv);
#define ClockPWM_Start() \
    ClockPWM_StartEx(ClockPWM__PA_DIV_ID)

#else

void ClockPWM_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ClockPWM_Stop(void);

void ClockPWM_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ClockPWM_GetDividerRegister(void);
uint8  ClockPWM_GetFractionalDividerRegister(void);

#define ClockPWM_Enable()                         ClockPWM_Start()
#define ClockPWM_Disable()                        ClockPWM_Stop()
#define ClockPWM_SetDividerRegister(clkDivider, reset)  \
    ClockPWM_SetFractionalDividerRegister((clkDivider), 0u)
#define ClockPWM_SetDivider(clkDivider)           ClockPWM_SetDividerRegister((clkDivider), 1u)
#define ClockPWM_SetDividerValue(clkDivider)      ClockPWM_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ClockPWM_DIV_ID     ClockPWM__DIV_ID

#define ClockPWM_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ClockPWM_CTRL_REG   (*(reg32 *)ClockPWM__CTRL_REGISTER)
#define ClockPWM_DIV_REG    (*(reg32 *)ClockPWM__DIV_REGISTER)

#define ClockPWM_CMD_DIV_SHIFT          (0u)
#define ClockPWM_CMD_PA_DIV_SHIFT       (8u)
#define ClockPWM_CMD_DISABLE_SHIFT      (30u)
#define ClockPWM_CMD_ENABLE_SHIFT       (31u)

#define ClockPWM_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ClockPWM_CMD_DISABLE_SHIFT))
#define ClockPWM_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ClockPWM_CMD_ENABLE_SHIFT))

#define ClockPWM_DIV_FRAC_MASK  (0x000000F8u)
#define ClockPWM_DIV_FRAC_SHIFT (3u)
#define ClockPWM_DIV_INT_MASK   (0xFFFFFF00u)
#define ClockPWM_DIV_INT_SHIFT  (8u)

#else 

#define ClockPWM_DIV_REG        (*(reg32 *)ClockPWM__REGISTER)
#define ClockPWM_ENABLE_REG     ClockPWM_DIV_REG
#define ClockPWM_DIV_FRAC_MASK  ClockPWM__FRAC_MASK
#define ClockPWM_DIV_FRAC_SHIFT (16u)
#define ClockPWM_DIV_INT_MASK   ClockPWM__DIVIDER_MASK
#define ClockPWM_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ClockPWM_H) */

/* [] END OF FILE */
