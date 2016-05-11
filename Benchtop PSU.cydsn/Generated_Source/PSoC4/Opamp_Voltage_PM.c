/*******************************************************************************
* File Name: Opamp_Voltage_PM.c
* Version 1.10
*
* Description:
*  This file provides the power management source code to the API for the
*  Opamp (Analog Buffer) component.
*
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Opamp_Voltage.h"

#if(!Opamp_Voltage_CHECK_DEEPSLEEP_SUPPORT)
    static Opamp_Voltage_BACKUP_STRUCT Opamp_Voltage_backup =
    {
        0u, /* enableState */
    };
#endif /* (Opamp_Voltage_CHECK_DEEPSLEEP_SUPPORT) */


/*******************************************************************************
* Function Name: Opamp_Voltage_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opamp_Voltage_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Opamp_Voltage_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opamp_Voltage_RestoreConfig(void)
{
    
}


/*******************************************************************************
* Function Name: Opamp_Voltage_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The Sleep() API 
*  saves the current component state. Call the Sleep() function before calling the 
*  CySysPmDeepSleep() or the CySysPmHibernate() functions. The "Deep sleep operation" 
*  option has an influence on this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opamp_Voltage_backup: The structure field 'enableState' is modified
*  depending on the enable state of the block before entering the sleep mode.
*
*******************************************************************************/
void Opamp_Voltage_Sleep(void)
{
#if(!Opamp_Voltage_CHECK_DEEPSLEEP_SUPPORT)
    if(Opamp_Voltage_CHECK_PWR_MODE_OFF)
    {
        Opamp_Voltage_backup.enableState = 1u;
        Opamp_Voltage_Stop();
    }
    else /* The component is disabled */
    {
        Opamp_Voltage_backup.enableState = 0u;
    }
#endif /* (Opamp_Voltage_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: Opamp_Voltage_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when Sleep() 
*  is called. If the component has been enabled before the Sleep() function is 
*  called, the Wakeup() function will also re-enable the component.
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opamp_Voltage_backup: The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Opamp_Voltage_Wakeup(void)
{
#if(!Opamp_Voltage_CHECK_DEEPSLEEP_SUPPORT)
    if(0u != Opamp_Voltage_backup.enableState)
    {
        /* Enable Opamp's operation */
        Opamp_Voltage_Enable();
    } /* Do nothing if Opamp was disabled before */
#endif /* (Opamp_Voltage_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
