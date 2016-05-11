/*******************************************************************************
* File Name: PINH.c  
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
#include "PINH.h"

static PINH_BACKUP_STRUCT  PINH_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PINH_Sleep
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
*  \snippet PINH_SUT.c usage_PINH_Sleep_Wakeup
*******************************************************************************/
void PINH_Sleep(void)
{
    #if defined(PINH__PC)
        PINH_backup.pcState = PINH_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PINH_backup.usbState = PINH_CR1_REG;
            PINH_USB_POWER_REG |= PINH_USBIO_ENTER_SLEEP;
            PINH_CR1_REG &= PINH_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PINH__SIO)
        PINH_backup.sioState = PINH_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PINH_SIO_REG &= (uint32)(~PINH_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PINH_Wakeup
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
*  Refer to PINH_Sleep() for an example usage.
*******************************************************************************/
void PINH_Wakeup(void)
{
    #if defined(PINH__PC)
        PINH_PC = PINH_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PINH_USB_POWER_REG &= PINH_USBIO_EXIT_SLEEP_PH1;
            PINH_CR1_REG = PINH_backup.usbState;
            PINH_USB_POWER_REG &= PINH_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PINH__SIO)
        PINH_SIO_REG = PINH_backup.sioState;
    #endif
}


/* [] END OF FILE */
