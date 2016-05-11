/*******************************************************************************
* File Name: ResetLCD.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "ResetLCD.h"

static ResetLCD_BACKUP_STRUCT  ResetLCD_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ResetLCD_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet ResetLCD_SUT.c usage_ResetLCD_Sleep_Wakeup
*******************************************************************************/
void ResetLCD_Sleep(void)
{
    #if defined(ResetLCD__PC)
        ResetLCD_backup.pcState = ResetLCD_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ResetLCD_backup.usbState = ResetLCD_CR1_REG;
            ResetLCD_USB_POWER_REG |= ResetLCD_USBIO_ENTER_SLEEP;
            ResetLCD_CR1_REG &= ResetLCD_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ResetLCD__SIO)
        ResetLCD_backup.sioState = ResetLCD_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ResetLCD_SIO_REG &= (uint32)(~ResetLCD_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ResetLCD_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to ResetLCD_Sleep() for an example usage.
*******************************************************************************/
void ResetLCD_Wakeup(void)
{
    #if defined(ResetLCD__PC)
        ResetLCD_PC = ResetLCD_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ResetLCD_USB_POWER_REG &= ResetLCD_USBIO_EXIT_SLEEP_PH1;
            ResetLCD_CR1_REG = ResetLCD_backup.usbState;
            ResetLCD_USB_POWER_REG &= ResetLCD_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ResetLCD__SIO)
        ResetLCD_SIO_REG = ResetLCD_backup.sioState;
    #endif
}


/* [] END OF FILE */
