/*******************************************************************************
* File Name: ADC_VC_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_VC.h"


/***************************************
* Local data allocation
***************************************/

static ADC_VC_BACKUP_STRUCT  ADC_VC_backup =
{
    ADC_VC_DISABLED
};


/*******************************************************************************
* Function Name: ADC_VC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_VC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_VC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_VC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_VC_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_VC_backup - modified.
*
*******************************************************************************/
void ADC_VC_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    ADC_VC_SAR_DFT_CTRL_REG |= ADC_VC_ADFT_OVERRIDE;
    if((ADC_VC_SAR_CTRL_REG  & ADC_VC_ENABLE) != 0u)
    {
        if((ADC_VC_SAR_SAMPLE_CTRL_REG & ADC_VC_CONTINUOUS_EN) != 0u)
        {
            ADC_VC_backup.enableState = ADC_VC_ENABLED | ADC_VC_STARTED;
        }
        else
        {
            ADC_VC_backup.enableState = ADC_VC_ENABLED;
        }
        ADC_VC_StopConvert();
        ADC_VC_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((ADC_VC_SAR_CTRL_REG & ADC_VC_BOOSTPUMP_EN) != 0u)
        {
            ADC_VC_SAR_CTRL_REG &= (uint32)~ADC_VC_BOOSTPUMP_EN;
            ADC_VC_backup.enableState |= ADC_VC_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        ADC_VC_backup.enableState = ADC_VC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_VC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_VC_backup - used.
*
*******************************************************************************/
void ADC_VC_Wakeup(void)
{
    ADC_VC_SAR_DFT_CTRL_REG &= (uint32)~ADC_VC_ADFT_OVERRIDE;
    if(ADC_VC_backup.enableState != ADC_VC_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((ADC_VC_backup.enableState & ADC_VC_BOOSTPUMP_ENABLED) != 0u)
        {
            ADC_VC_SAR_CTRL_REG |= ADC_VC_BOOSTPUMP_EN;
        }
        ADC_VC_Enable();
        if((ADC_VC_backup.enableState & ADC_VC_STARTED) != 0u)
        {
            ADC_VC_StartConvert();
        }
    }
}
/* [] END OF FILE */
