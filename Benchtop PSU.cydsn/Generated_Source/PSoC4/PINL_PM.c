/*******************************************************************************
* File Name: PINL.c  
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
#include "PINL.h"

static PINL_BACKUP_STRUCT  PINL_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PINL_Sleep
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
*  \snippet PINL_SUT.c usage_PINL_Sleep_Wakeup
*******************************************************************************/
void PINL_Sleep(void)
{
    #if defined(PINL__PC)
        PINL_backup.pcState = PINL_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PINL_backup.usbState = PINL_CR1_REG;
            PINL_USB_POWER_REG |= PINL_USBIO_ENTER_SLEEP;
            PINL_CR1_REG &= PINL_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PINL__SIO)
        PINL_backup.sioState = PINL_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PINL_SIO_REG &= (uint32)(~PINL_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PINL_Wakeup
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
*  Refer to PINL_Sleep() for an example usage.
*******************************************************************************/
void PINL_Wakeup(void)
{
    #if defined(PINL__PC)
        PINL_PC = PINL_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PINL_USB_POWER_REG &= PINL_USBIO_EXIT_SLEEP_PH1;
            PINL_CR1_REG = PINL_backup.usbState;
            PINL_USB_POWER_REG &= PINL_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PINL__SIO)
        PINL_SIO_REG = PINL_backup.sioState;
    #endif
}


/* [] END OF FILE */
