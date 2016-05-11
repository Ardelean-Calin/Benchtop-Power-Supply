/*******************************************************************************
* File Name: ResetLCD.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ResetLCD_H) /* Pins ResetLCD_H */
#define CY_PINS_ResetLCD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ResetLCD_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} ResetLCD_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ResetLCD_Read(void);
void    ResetLCD_Write(uint8 value);
uint8   ResetLCD_ReadDataReg(void);
#if defined(ResetLCD__PC) || (CY_PSOC4_4200L) 
    void    ResetLCD_SetDriveMode(uint8 mode);
#endif
void    ResetLCD_SetInterruptMode(uint16 position, uint16 mode);
uint8   ResetLCD_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ResetLCD_Sleep(void); 
void ResetLCD_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ResetLCD__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ResetLCD_DRIVE_MODE_BITS        (3)
    #define ResetLCD_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ResetLCD_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ResetLCD_SetDriveMode() function.
         *  @{
         */
        #define ResetLCD_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ResetLCD_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ResetLCD_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ResetLCD_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ResetLCD_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ResetLCD_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ResetLCD_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ResetLCD_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ResetLCD_MASK               ResetLCD__MASK
#define ResetLCD_SHIFT              ResetLCD__SHIFT
#define ResetLCD_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ResetLCD_SetInterruptMode() function.
     *  @{
     */
        #define ResetLCD_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ResetLCD_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ResetLCD_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ResetLCD_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ResetLCD__SIO)
    #define ResetLCD_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ResetLCD__PC) && (CY_PSOC4_4200L)
    #define ResetLCD_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ResetLCD_USBIO_DISABLE              ((uint32)(~ResetLCD_USBIO_ENABLE))
    #define ResetLCD_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ResetLCD_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ResetLCD_USBIO_ENTER_SLEEP          ((uint32)((1u << ResetLCD_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ResetLCD_USBIO_SUSPEND_DEL_SHIFT)))
    #define ResetLCD_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ResetLCD_USBIO_SUSPEND_SHIFT)))
    #define ResetLCD_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ResetLCD_USBIO_SUSPEND_DEL_SHIFT)))
    #define ResetLCD_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ResetLCD__PC)
    /* Port Configuration */
    #define ResetLCD_PC                 (* (reg32 *) ResetLCD__PC)
#endif
/* Pin State */
#define ResetLCD_PS                     (* (reg32 *) ResetLCD__PS)
/* Data Register */
#define ResetLCD_DR                     (* (reg32 *) ResetLCD__DR)
/* Input Buffer Disable Override */
#define ResetLCD_INP_DIS                (* (reg32 *) ResetLCD__PC2)

/* Interrupt configuration Registers */
#define ResetLCD_INTCFG                 (* (reg32 *) ResetLCD__INTCFG)
#define ResetLCD_INTSTAT                (* (reg32 *) ResetLCD__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ResetLCD_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ResetLCD__SIO)
    #define ResetLCD_SIO_REG            (* (reg32 *) ResetLCD__SIO)
#endif /* (ResetLCD__SIO_CFG) */

/* USBIO registers */
#if !defined(ResetLCD__PC) && (CY_PSOC4_4200L)
    #define ResetLCD_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ResetLCD_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ResetLCD_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ResetLCD_DRIVE_MODE_SHIFT       (0x00u)
#define ResetLCD_DRIVE_MODE_MASK        (0x07u << ResetLCD_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ResetLCD_H */


/* [] END OF FILE */
