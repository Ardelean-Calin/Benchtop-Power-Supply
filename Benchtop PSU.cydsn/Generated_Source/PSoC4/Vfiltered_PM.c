/*******************************************************************************
* File Name: Vfiltered.c  
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
#include "Vfiltered.h"

static Vfiltered_BACKUP_STRUCT  Vfiltered_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Vfiltered_Sleep
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
*  \snippet Vfiltered_SUT.c usage_Vfiltered_Sleep_Wakeup
*******************************************************************************/
void Vfiltered_Sleep(void)
{
    #if defined(Vfiltered__PC)
        Vfiltered_backup.pcState = Vfiltered_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Vfiltered_backup.usbState = Vfiltered_CR1_REG;
            Vfiltered_USB_POWER_REG |= Vfiltered_USBIO_ENTER_SLEEP;
            Vfiltered_CR1_REG &= Vfiltered_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vfiltered__SIO)
        Vfiltered_backup.sioState = Vfiltered_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Vfiltered_SIO_REG &= (uint32)(~Vfiltered_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Vfiltered_Wakeup
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
*  Refer to Vfiltered_Sleep() for an example usage.
*******************************************************************************/
void Vfiltered_Wakeup(void)
{
    #if defined(Vfiltered__PC)
        Vfiltered_PC = Vfiltered_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Vfiltered_USB_POWER_REG &= Vfiltered_USBIO_EXIT_SLEEP_PH1;
            Vfiltered_CR1_REG = Vfiltered_backup.usbState;
            Vfiltered_USB_POWER_REG &= Vfiltered_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vfiltered__SIO)
        Vfiltered_SIO_REG = Vfiltered_backup.sioState;
    #endif
}


/* [] END OF FILE */
