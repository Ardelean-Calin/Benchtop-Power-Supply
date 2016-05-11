/*******************************************************************************
* File Name: An_c.h  
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

#if !defined(CY_PINS_An_c_H) /* Pins An_c_H */
#define CY_PINS_An_c_H

#include "cytypes.h"
#include "cyfitter.h"
#include "An_c_aliases.h"


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
} An_c_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   An_c_Read(void);
void    An_c_Write(uint8 value);
uint8   An_c_ReadDataReg(void);
#if defined(An_c__PC) || (CY_PSOC4_4200L) 
    void    An_c_SetDriveMode(uint8 mode);
#endif
void    An_c_SetInterruptMode(uint16 position, uint16 mode);
uint8   An_c_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void An_c_Sleep(void); 
void An_c_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(An_c__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define An_c_DRIVE_MODE_BITS        (3)
    #define An_c_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - An_c_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the An_c_SetDriveMode() function.
         *  @{
         */
        #define An_c_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define An_c_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define An_c_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define An_c_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define An_c_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define An_c_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define An_c_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define An_c_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define An_c_MASK               An_c__MASK
#define An_c_SHIFT              An_c__SHIFT
#define An_c_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in An_c_SetInterruptMode() function.
     *  @{
     */
        #define An_c_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define An_c_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define An_c_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define An_c_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(An_c__SIO)
    #define An_c_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(An_c__PC) && (CY_PSOC4_4200L)
    #define An_c_USBIO_ENABLE               ((uint32)0x80000000u)
    #define An_c_USBIO_DISABLE              ((uint32)(~An_c_USBIO_ENABLE))
    #define An_c_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define An_c_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define An_c_USBIO_ENTER_SLEEP          ((uint32)((1u << An_c_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << An_c_USBIO_SUSPEND_DEL_SHIFT)))
    #define An_c_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << An_c_USBIO_SUSPEND_SHIFT)))
    #define An_c_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << An_c_USBIO_SUSPEND_DEL_SHIFT)))
    #define An_c_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(An_c__PC)
    /* Port Configuration */
    #define An_c_PC                 (* (reg32 *) An_c__PC)
#endif
/* Pin State */
#define An_c_PS                     (* (reg32 *) An_c__PS)
/* Data Register */
#define An_c_DR                     (* (reg32 *) An_c__DR)
/* Input Buffer Disable Override */
#define An_c_INP_DIS                (* (reg32 *) An_c__PC2)

/* Interrupt configuration Registers */
#define An_c_INTCFG                 (* (reg32 *) An_c__INTCFG)
#define An_c_INTSTAT                (* (reg32 *) An_c__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define An_c_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(An_c__SIO)
    #define An_c_SIO_REG            (* (reg32 *) An_c__SIO)
#endif /* (An_c__SIO_CFG) */

/* USBIO registers */
#if !defined(An_c__PC) && (CY_PSOC4_4200L)
    #define An_c_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define An_c_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define An_c_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define An_c_DRIVE_MODE_SHIFT       (0x00u)
#define An_c_DRIVE_MODE_MASK        (0x07u << An_c_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins An_c_H */


/* [] END OF FILE */
