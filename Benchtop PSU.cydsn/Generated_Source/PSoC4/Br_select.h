/*******************************************************************************
* File Name: Br_select.h  
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

#if !defined(CY_PINS_Br_select_H) /* Pins Br_select_H */
#define CY_PINS_Br_select_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Br_select_aliases.h"


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
} Br_select_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Br_select_Read(void);
void    Br_select_Write(uint8 value);
uint8   Br_select_ReadDataReg(void);
#if defined(Br_select__PC) || (CY_PSOC4_4200L) 
    void    Br_select_SetDriveMode(uint8 mode);
#endif
void    Br_select_SetInterruptMode(uint16 position, uint16 mode);
uint8   Br_select_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Br_select_Sleep(void); 
void Br_select_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Br_select__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Br_select_DRIVE_MODE_BITS        (3)
    #define Br_select_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Br_select_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Br_select_SetDriveMode() function.
         *  @{
         */
        #define Br_select_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Br_select_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Br_select_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Br_select_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Br_select_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Br_select_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Br_select_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Br_select_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Br_select_MASK               Br_select__MASK
#define Br_select_SHIFT              Br_select__SHIFT
#define Br_select_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Br_select_SetInterruptMode() function.
     *  @{
     */
        #define Br_select_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Br_select_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Br_select_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Br_select_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Br_select__SIO)
    #define Br_select_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Br_select__PC) && (CY_PSOC4_4200L)
    #define Br_select_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Br_select_USBIO_DISABLE              ((uint32)(~Br_select_USBIO_ENABLE))
    #define Br_select_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Br_select_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Br_select_USBIO_ENTER_SLEEP          ((uint32)((1u << Br_select_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Br_select_USBIO_SUSPEND_DEL_SHIFT)))
    #define Br_select_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Br_select_USBIO_SUSPEND_SHIFT)))
    #define Br_select_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Br_select_USBIO_SUSPEND_DEL_SHIFT)))
    #define Br_select_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Br_select__PC)
    /* Port Configuration */
    #define Br_select_PC                 (* (reg32 *) Br_select__PC)
#endif
/* Pin State */
#define Br_select_PS                     (* (reg32 *) Br_select__PS)
/* Data Register */
#define Br_select_DR                     (* (reg32 *) Br_select__DR)
/* Input Buffer Disable Override */
#define Br_select_INP_DIS                (* (reg32 *) Br_select__PC2)

/* Interrupt configuration Registers */
#define Br_select_INTCFG                 (* (reg32 *) Br_select__INTCFG)
#define Br_select_INTSTAT                (* (reg32 *) Br_select__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Br_select_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Br_select__SIO)
    #define Br_select_SIO_REG            (* (reg32 *) Br_select__SIO)
#endif /* (Br_select__SIO_CFG) */

/* USBIO registers */
#if !defined(Br_select__PC) && (CY_PSOC4_4200L)
    #define Br_select_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Br_select_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Br_select_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Br_select_DRIVE_MODE_SHIFT       (0x00u)
#define Br_select_DRIVE_MODE_MASK        (0x07u << Br_select_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Br_select_H */


/* [] END OF FILE */
