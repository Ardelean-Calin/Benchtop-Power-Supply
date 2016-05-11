/*******************************************************************************
* File Name: TestAmp.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the Opamp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TestAmp.h"

uint8 TestAmp_initVar = 0u; /* Defines if component was initialized */
static uint32 TestAmp_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: TestAmp_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TestAmp_Init(void)
{
    TestAmp_internalPower = TestAmp_POWER;
    TestAmp_CTB_CTRL_REG = TestAmp_DEFAULT_CTB_CTRL;
    TestAmp_OA_RES_CTRL_REG = TestAmp_DEFAULT_OA_RES_CTRL;
    TestAmp_OA_COMP_TRIM_REG = TestAmp_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: TestAmp_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TestAmp_Enable(void)
{
    TestAmp_OA_RES_CTRL_REG |= TestAmp_internalPower | \
                                        TestAmp_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: TestAmp_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables power 
*  to the block. The first time the routine is executed, the Power level, Mode, 
*  and Output mode are set. When called to restart the Opamp following a Stop() call, 
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TestAmp_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void TestAmp_Start(void)
{
    if( 0u == TestAmp_initVar)
    {
        TestAmp_Init();
        TestAmp_initVar = 1u;
    }
    TestAmp_Enable();
}


/*******************************************************************************
* Function Name: TestAmp_Stop
********************************************************************************
*
* Summary:
*  Turn off the Opamp block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TestAmp_Stop(void)
{
    TestAmp_OA_RES_CTRL_REG &= ((uint32)~(TestAmp_OA_PWR_MODE_MASK | \
                                                   TestAmp_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: TestAmp_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   TestAmp_LOW_POWER - Lowest active power
*   TestAmp_MED_POWER - Medium power
*   TestAmp_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void TestAmp_SetPower(uint32 power)
{
    uint32 tmp;
    
    TestAmp_internalPower = TestAmp_GET_OA_PWR_MODE(power);
    tmp = TestAmp_OA_RES_CTRL_REG & \
           (uint32)~TestAmp_OA_PWR_MODE_MASK;
    TestAmp_OA_RES_CTRL_REG = tmp | TestAmp_internalPower;
}


/*******************************************************************************
* Function Name: TestAmp_PumpControl
********************************************************************************
*
* Summary:
*  Allows the user to turn the Opamp's boost pump on or off. By Default the Start() 
*  function turns on the pump. Use this API to turn it off. The boost must be 
*  turned on when the supply is less than 2.7 volts and off if the supply is more 
*  than 4 volts.
*
* Parameters:
*  onOff: Control the pump.
*   TestAmp_PUMP_OFF - Turn off the pump
*   TestAmp_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void TestAmp_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        TestAmp_OA_RES_CTRL |= TestAmp_OA_PUMP_EN;    
    }
    else
    {
        TestAmp_OA_RES_CTRL &= (uint32)~TestAmp_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
