/*******************************************************************************
* File Name: OA_minus.c  
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
#include "OA_minus.h"

static OA_minus_BACKUP_STRUCT  OA_minus_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: OA_minus_Sleep
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
*  \snippet OA_minus_SUT.c usage_OA_minus_Sleep_Wakeup
*******************************************************************************/
void OA_minus_Sleep(void)
{
    #if defined(OA_minus__PC)
        OA_minus_backup.pcState = OA_minus_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            OA_minus_backup.usbState = OA_minus_CR1_REG;
            OA_minus_USB_POWER_REG |= OA_minus_USBIO_ENTER_SLEEP;
            OA_minus_CR1_REG &= OA_minus_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(OA_minus__SIO)
        OA_minus_backup.sioState = OA_minus_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        OA_minus_SIO_REG &= (uint32)(~OA_minus_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: OA_minus_Wakeup
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
*  Refer to OA_minus_Sleep() for an example usage.
*******************************************************************************/
void OA_minus_Wakeup(void)
{
    #if defined(OA_minus__PC)
        OA_minus_PC = OA_minus_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            OA_minus_USB_POWER_REG &= OA_minus_USBIO_EXIT_SLEEP_PH1;
            OA_minus_CR1_REG = OA_minus_backup.usbState;
            OA_minus_USB_POWER_REG &= OA_minus_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(OA_minus__SIO)
        OA_minus_SIO_REG = OA_minus_backup.sioState;
    #endif
}


/* [] END OF FILE */
