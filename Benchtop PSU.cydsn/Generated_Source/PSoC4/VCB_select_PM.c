/*******************************************************************************
* File Name: VCB_select.c  
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
#include "VCB_select.h"

static VCB_select_BACKUP_STRUCT  VCB_select_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: VCB_select_Sleep
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
*  \snippet VCB_select_SUT.c usage_VCB_select_Sleep_Wakeup
*******************************************************************************/
void VCB_select_Sleep(void)
{
    #if defined(VCB_select__PC)
        VCB_select_backup.pcState = VCB_select_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            VCB_select_backup.usbState = VCB_select_CR1_REG;
            VCB_select_USB_POWER_REG |= VCB_select_USBIO_ENTER_SLEEP;
            VCB_select_CR1_REG &= VCB_select_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(VCB_select__SIO)
        VCB_select_backup.sioState = VCB_select_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        VCB_select_SIO_REG &= (uint32)(~VCB_select_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: VCB_select_Wakeup
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
*  Refer to VCB_select_Sleep() for an example usage.
*******************************************************************************/
void VCB_select_Wakeup(void)
{
    #if defined(VCB_select__PC)
        VCB_select_PC = VCB_select_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            VCB_select_USB_POWER_REG &= VCB_select_USBIO_EXIT_SLEEP_PH1;
            VCB_select_CR1_REG = VCB_select_backup.usbState;
            VCB_select_USB_POWER_REG &= VCB_select_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(VCB_select__SIO)
        VCB_select_SIO_REG = VCB_select_backup.sioState;
    #endif
}


/* [] END OF FILE */
