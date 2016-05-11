/*******************************************************************************
* File Name: An_c.c  
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
#include "An_c.h"

static An_c_BACKUP_STRUCT  An_c_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: An_c_Sleep
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
*  \snippet An_c_SUT.c usage_An_c_Sleep_Wakeup
*******************************************************************************/
void An_c_Sleep(void)
{
    #if defined(An_c__PC)
        An_c_backup.pcState = An_c_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            An_c_backup.usbState = An_c_CR1_REG;
            An_c_USB_POWER_REG |= An_c_USBIO_ENTER_SLEEP;
            An_c_CR1_REG &= An_c_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(An_c__SIO)
        An_c_backup.sioState = An_c_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        An_c_SIO_REG &= (uint32)(~An_c_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: An_c_Wakeup
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
*  Refer to An_c_Sleep() for an example usage.
*******************************************************************************/
void An_c_Wakeup(void)
{
    #if defined(An_c__PC)
        An_c_PC = An_c_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            An_c_USB_POWER_REG &= An_c_USBIO_EXIT_SLEEP_PH1;
            An_c_CR1_REG = An_c_backup.usbState;
            An_c_USB_POWER_REG &= An_c_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(An_c__SIO)
        An_c_SIO_REG = An_c_backup.sioState;
    #endif
}


/* [] END OF FILE */
