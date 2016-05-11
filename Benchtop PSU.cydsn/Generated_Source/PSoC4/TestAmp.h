/*******************************************************************************
* File Name: TestAmp.h
* Version 1.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_TestAmp_H)
#define CY_OPAMP_TestAmp_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} TestAmp_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void TestAmp_Init(void);
void TestAmp_Enable(void);
void TestAmp_Start(void);
void TestAmp_Stop(void);
void TestAmp_SetPower(uint32 power);
void TestAmp_PumpControl(uint32 onOff);
void TestAmp_Sleep(void);
void TestAmp_Wakeup(void);
void TestAmp_SaveConfig(void);
void TestAmp_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define TestAmp_LOW_POWER      (1u)
#define TestAmp_MED_POWER      (2u)
#define TestAmp_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define TestAmp_PUMP_ON        (1u)
#define TestAmp_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define TestAmp_OUTPUT_CURRENT         (1u)
#define TestAmp_POWER                  (3u)
#define TestAmp_MODE                   (1u)
#define TestAmp_OA_COMP_TRIM_VALUE     (3u)
#define TestAmp_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  TestAmp_initVar;


/**************************************
*             Registers
**************************************/
#define TestAmp_CTB_CTRL_REG       (*(reg32 *) TestAmp_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define TestAmp_CTB_CTRL_PTR       ( (reg32 *) TestAmp_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define TestAmp_OA_RES_CTRL_REG    (*(reg32 *) TestAmp_cy_psoc4_abuf__OA_RES_CTRL)
#define TestAmp_OA_RES_CTRL_PTR    ( (reg32 *) TestAmp_cy_psoc4_abuf__OA_RES_CTRL)
#define TestAmp_OA_COMP_TRIM_REG   (*(reg32 *) TestAmp_cy_psoc4_abuf__OA_COMP_TRIM)
#define TestAmp_OA_COMP_TRIM_PTR   ( (reg32 *) TestAmp_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* TestAmp_CTB_CTRL_REG */
#define TestAmp_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define TestAmp_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define TestAmp_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << TestAmp_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define TestAmp_CTB_CTRL_ENABLED               ((uint32) 0x01u << TestAmp_CTB_CTRL_ENABLED_SHIFT)


/* TestAmp_OA_RES_CTRL_REG */
#define TestAmp_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define TestAmp_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define TestAmp_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define TestAmp_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define TestAmp_OA_PWR_MODE                ((uint32) 0x02u << TestAmp_OA_PWR_MODE_SHIFT)
#define TestAmp_OA_PWR_MODE_MASK           ((uint32) 0x03u << TestAmp_OA_PWR_MODE_SHIFT)
#define TestAmp_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << TestAmp_OA_DRIVE_STR_SEL_SHIFT)
#define TestAmp_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << TestAmp_OA_DRIVE_STR_SEL_SHIFT)
#define TestAmp_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << TestAmp_OA_DRIVE_STR_SEL_SHIFT)
#define TestAmp_OA_COMP_EN                 ((uint32) 0x00u << TestAmp_OA_COMP_EN_SHIFT)
#define TestAmp_OA_PUMP_EN                 ((uint32) 0x01u << TestAmp_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define TestAmp_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (TestAmp_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define TestAmp_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (TestAmp_OA_DRIVE_STR_SEL_10X) : \
                                                                             (TestAmp_OA_DRIVE_STR_SEL_1X))
#define TestAmp_GET_OA_PWR_MODE(mode)          ((mode) & TestAmp_OA_PWR_MODE_MASK)
#define TestAmp_CHECK_PWR_MODE_OFF             (0u != (TestAmp_OA_RES_CTRL_REG & \
                                                                TestAmp_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define TestAmp_CHECK_DEEPSLEEP_SUPPORT        (0u != TestAmp_DEEPSLEEP_SUPPORT) 

#define TestAmp_DEFAULT_CTB_CTRL (TestAmp_GET_DEEPSLEEP_ON(TestAmp_DEEPSLEEP_SUPPORT) | \
                                           TestAmp_CTB_CTRL_ENABLED)

#define TestAmp_DEFAULT_OA_RES_CTRL (TestAmp_OA_COMP_EN | \
                                              TestAmp_GET_OA_DRIVE_STR(TestAmp_OUTPUT_CURRENT))

#define TestAmp_DEFAULT_OA_COMP_TRIM_REG (TestAmp_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define TestAmp_LOWPOWER                   (TestAmp_LOW_POWER)
#define TestAmp_MEDPOWER                   (TestAmp_MED_POWER)
#define TestAmp_HIGHPOWER                  (TestAmp_HIGH_POWER)

/* PUMP ON/OFF defines */
#define TestAmp_PUMPON                     (TestAmp_PUMP_ON)
#define TestAmp_PUMPOFF                    (TestAmp_PUMP_OFF)

#define TestAmp_OA_CTRL                    (TestAmp_CTB_CTRL_REG)
#define TestAmp_OA_RES_CTRL                (TestAmp_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define TestAmp_OA_CTB_EN_SHIFT            (TestAmp_CTB_CTRL_ENABLED_SHIFT)
#define TestAmp_OA_PUMP_CTRL_SHIFT         (TestAmp_OA_PUMP_EN_SHIFT)
#define TestAmp_OA_PUMP_EN_MASK            (0x800u)
#define TestAmp_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_TestAmp_H */


/* [] END OF FILE */
