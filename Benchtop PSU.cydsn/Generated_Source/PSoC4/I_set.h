/*******************************************************************************
* File Name: I_set.h  
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

#if !defined(CY_PINS_I_set_H) /* Pins I_set_H */
#define CY_PINS_I_set_H

#include "cytypes.h"
#include "cyfitter.h"
#include "I_set_aliases.h"


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
} I_set_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   I_set_Read(void);
void    I_set_Write(uint8 value);
uint8   I_set_ReadDataReg(void);
#if defined(I_set__PC) || (CY_PSOC4_4200L) 
    void    I_set_SetDriveMode(uint8 mode);
#endif
void    I_set_SetInterruptMode(uint16 position, uint16 mode);
uint8   I_set_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void I_set_Sleep(void); 
void I_set_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(I_set__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define I_set_DRIVE_MODE_BITS        (3)
    #define I_set_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - I_set_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the I_set_SetDriveMode() function.
         *  @{
         */
        #define I_set_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define I_set_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define I_set_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define I_set_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define I_set_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define I_set_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define I_set_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define I_set_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define I_set_MASK               I_set__MASK
#define I_set_SHIFT              I_set__SHIFT
#define I_set_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in I_set_SetInterruptMode() function.
     *  @{
     */
        #define I_set_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define I_set_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define I_set_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define I_set_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(I_set__SIO)
    #define I_set_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(I_set__PC) && (CY_PSOC4_4200L)
    #define I_set_USBIO_ENABLE               ((uint32)0x80000000u)
    #define I_set_USBIO_DISABLE              ((uint32)(~I_set_USBIO_ENABLE))
    #define I_set_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define I_set_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define I_set_USBIO_ENTER_SLEEP          ((uint32)((1u << I_set_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << I_set_USBIO_SUSPEND_DEL_SHIFT)))
    #define I_set_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << I_set_USBIO_SUSPEND_SHIFT)))
    #define I_set_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << I_set_USBIO_SUSPEND_DEL_SHIFT)))
    #define I_set_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(I_set__PC)
    /* Port Configuration */
    #define I_set_PC                 (* (reg32 *) I_set__PC)
#endif
/* Pin State */
#define I_set_PS                     (* (reg32 *) I_set__PS)
/* Data Register */
#define I_set_DR                     (* (reg32 *) I_set__DR)
/* Input Buffer Disable Override */
#define I_set_INP_DIS                (* (reg32 *) I_set__PC2)

/* Interrupt configuration Registers */
#define I_set_INTCFG                 (* (reg32 *) I_set__INTCFG)
#define I_set_INTSTAT                (* (reg32 *) I_set__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define I_set_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(I_set__SIO)
    #define I_set_SIO_REG            (* (reg32 *) I_set__SIO)
#endif /* (I_set__SIO_CFG) */

/* USBIO registers */
#if !defined(I_set__PC) && (CY_PSOC4_4200L)
    #define I_set_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define I_set_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define I_set_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define I_set_DRIVE_MODE_SHIFT       (0x00u)
#define I_set_DRIVE_MODE_MASK        (0x07u << I_set_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins I_set_H */


/* [] END OF FILE */
