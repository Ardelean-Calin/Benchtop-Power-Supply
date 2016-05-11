/*******************************************************************************
* File Name: VCB_select.h  
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

#if !defined(CY_PINS_VCB_select_H) /* Pins VCB_select_H */
#define CY_PINS_VCB_select_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VCB_select_aliases.h"


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
} VCB_select_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VCB_select_Read(void);
void    VCB_select_Write(uint8 value);
uint8   VCB_select_ReadDataReg(void);
#if defined(VCB_select__PC) || (CY_PSOC4_4200L) 
    void    VCB_select_SetDriveMode(uint8 mode);
#endif
void    VCB_select_SetInterruptMode(uint16 position, uint16 mode);
uint8   VCB_select_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VCB_select_Sleep(void); 
void VCB_select_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VCB_select__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VCB_select_DRIVE_MODE_BITS        (3)
    #define VCB_select_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VCB_select_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VCB_select_SetDriveMode() function.
         *  @{
         */
        #define VCB_select_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VCB_select_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VCB_select_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VCB_select_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VCB_select_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VCB_select_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VCB_select_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VCB_select_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VCB_select_MASK               VCB_select__MASK
#define VCB_select_SHIFT              VCB_select__SHIFT
#define VCB_select_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VCB_select_SetInterruptMode() function.
     *  @{
     */
        #define VCB_select_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VCB_select_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VCB_select_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VCB_select_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VCB_select__SIO)
    #define VCB_select_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VCB_select__PC) && (CY_PSOC4_4200L)
    #define VCB_select_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VCB_select_USBIO_DISABLE              ((uint32)(~VCB_select_USBIO_ENABLE))
    #define VCB_select_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VCB_select_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VCB_select_USBIO_ENTER_SLEEP          ((uint32)((1u << VCB_select_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VCB_select_USBIO_SUSPEND_DEL_SHIFT)))
    #define VCB_select_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VCB_select_USBIO_SUSPEND_SHIFT)))
    #define VCB_select_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VCB_select_USBIO_SUSPEND_DEL_SHIFT)))
    #define VCB_select_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VCB_select__PC)
    /* Port Configuration */
    #define VCB_select_PC                 (* (reg32 *) VCB_select__PC)
#endif
/* Pin State */
#define VCB_select_PS                     (* (reg32 *) VCB_select__PS)
/* Data Register */
#define VCB_select_DR                     (* (reg32 *) VCB_select__DR)
/* Input Buffer Disable Override */
#define VCB_select_INP_DIS                (* (reg32 *) VCB_select__PC2)

/* Interrupt configuration Registers */
#define VCB_select_INTCFG                 (* (reg32 *) VCB_select__INTCFG)
#define VCB_select_INTSTAT                (* (reg32 *) VCB_select__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VCB_select_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VCB_select__SIO)
    #define VCB_select_SIO_REG            (* (reg32 *) VCB_select__SIO)
#endif /* (VCB_select__SIO_CFG) */

/* USBIO registers */
#if !defined(VCB_select__PC) && (CY_PSOC4_4200L)
    #define VCB_select_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VCB_select_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VCB_select_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VCB_select_DRIVE_MODE_SHIFT       (0x00u)
#define VCB_select_DRIVE_MODE_MASK        (0x07u << VCB_select_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VCB_select_H */


/* [] END OF FILE */
