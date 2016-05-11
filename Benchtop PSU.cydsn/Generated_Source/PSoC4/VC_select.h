/*******************************************************************************
* File Name: VC_select.h  
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

#if !defined(CY_PINS_VC_select_H) /* Pins VC_select_H */
#define CY_PINS_VC_select_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VC_select_aliases.h"


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
} VC_select_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VC_select_Read(void);
void    VC_select_Write(uint8 value);
uint8   VC_select_ReadDataReg(void);
#if defined(VC_select__PC) || (CY_PSOC4_4200L) 
    void    VC_select_SetDriveMode(uint8 mode);
#endif
void    VC_select_SetInterruptMode(uint16 position, uint16 mode);
uint8   VC_select_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VC_select_Sleep(void); 
void VC_select_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VC_select__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VC_select_DRIVE_MODE_BITS        (3)
    #define VC_select_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VC_select_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VC_select_SetDriveMode() function.
         *  @{
         */
        #define VC_select_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VC_select_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VC_select_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VC_select_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VC_select_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VC_select_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VC_select_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VC_select_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VC_select_MASK               VC_select__MASK
#define VC_select_SHIFT              VC_select__SHIFT
#define VC_select_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VC_select_SetInterruptMode() function.
     *  @{
     */
        #define VC_select_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VC_select_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VC_select_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VC_select_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VC_select__SIO)
    #define VC_select_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VC_select__PC) && (CY_PSOC4_4200L)
    #define VC_select_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VC_select_USBIO_DISABLE              ((uint32)(~VC_select_USBIO_ENABLE))
    #define VC_select_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VC_select_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VC_select_USBIO_ENTER_SLEEP          ((uint32)((1u << VC_select_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VC_select_USBIO_SUSPEND_DEL_SHIFT)))
    #define VC_select_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VC_select_USBIO_SUSPEND_SHIFT)))
    #define VC_select_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VC_select_USBIO_SUSPEND_DEL_SHIFT)))
    #define VC_select_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VC_select__PC)
    /* Port Configuration */
    #define VC_select_PC                 (* (reg32 *) VC_select__PC)
#endif
/* Pin State */
#define VC_select_PS                     (* (reg32 *) VC_select__PS)
/* Data Register */
#define VC_select_DR                     (* (reg32 *) VC_select__DR)
/* Input Buffer Disable Override */
#define VC_select_INP_DIS                (* (reg32 *) VC_select__PC2)

/* Interrupt configuration Registers */
#define VC_select_INTCFG                 (* (reg32 *) VC_select__INTCFG)
#define VC_select_INTSTAT                (* (reg32 *) VC_select__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VC_select_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VC_select__SIO)
    #define VC_select_SIO_REG            (* (reg32 *) VC_select__SIO)
#endif /* (VC_select__SIO_CFG) */

/* USBIO registers */
#if !defined(VC_select__PC) && (CY_PSOC4_4200L)
    #define VC_select_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VC_select_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VC_select_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VC_select_DRIVE_MODE_SHIFT       (0x00u)
#define VC_select_DRIVE_MODE_MASK        (0x07u << VC_select_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VC_select_H */


/* [] END OF FILE */
