/*******************************************************************************
* File Name: VC_select.c  
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
#include "VC_select.h"

static VC_select_BACKUP_STRUCT  VC_select_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: VC_select_Sleep
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
*  \snippet VC_select_SUT.c usage_VC_select_Sleep_Wakeup
*******************************************************************************/
void VC_select_Sleep(void)
{
    #if defined(VC_select__PC)
        VC_select_backup.pcState = VC_select_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            VC_select_backup.usbState = VC_select_CR1_REG;
            VC_select_USB_POWER_REG |= VC_select_USBIO_ENTER_SLEEP;
            VC_select_CR1_REG &= VC_select_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(VC_select__SIO)
        VC_select_backup.sioState = VC_select_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        VC_select_SIO_REG &= (uint32)(~VC_select_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: VC_select_Wakeup
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
*  Refer to VC_select_Sleep() for an example usage.
*******************************************************************************/
void VC_select_Wakeup(void)
{
    #if defined(VC_select__PC)
        VC_select_PC = VC_select_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            VC_select_USB_POWER_REG &= VC_select_USBIO_EXIT_SLEEP_PH1;
            VC_select_CR1_REG = VC_select_backup.usbState;
            VC_select_USB_POWER_REG &= VC_select_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(VC_select__SIO)
        VC_select_SIO_REG = VC_select_backup.sioState;
    #endif
}


/* [] END OF FILE */
