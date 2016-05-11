/*******************************************************************************
* File Name: PINL.h  
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

#if !defined(CY_PINS_PINL_H) /* Pins PINL_H */
#define CY_PINS_PINL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PINL_aliases.h"


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
} PINL_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PINL_Read(void);
void    PINL_Write(uint8 value);
uint8   PINL_ReadDataReg(void);
#if defined(PINL__PC) || (CY_PSOC4_4200L) 
    void    PINL_SetDriveMode(uint8 mode);
#endif
void    PINL_SetInterruptMode(uint16 position, uint16 mode);
uint8   PINL_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PINL_Sleep(void); 
void PINL_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PINL__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PINL_DRIVE_MODE_BITS        (3)
    #define PINL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PINL_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PINL_SetDriveMode() function.
         *  @{
         */
        #define PINL_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PINL_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PINL_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PINL_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PINL_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PINL_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PINL_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PINL_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PINL_MASK               PINL__MASK
#define PINL_SHIFT              PINL__SHIFT
#define PINL_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PINL_SetInterruptMode() function.
     *  @{
     */
        #define PINL_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PINL_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PINL_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PINL_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PINL__SIO)
    #define PINL_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PINL__PC) && (CY_PSOC4_4200L)
    #define PINL_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PINL_USBIO_DISABLE              ((uint32)(~PINL_USBIO_ENABLE))
    #define PINL_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PINL_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PINL_USBIO_ENTER_SLEEP          ((uint32)((1u << PINL_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PINL_USBIO_SUSPEND_DEL_SHIFT)))
    #define PINL_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PINL_USBIO_SUSPEND_SHIFT)))
    #define PINL_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PINL_USBIO_SUSPEND_DEL_SHIFT)))
    #define PINL_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PINL__PC)
    /* Port Configuration */
    #define PINL_PC                 (* (reg32 *) PINL__PC)
#endif
/* Pin State */
#define PINL_PS                     (* (reg32 *) PINL__PS)
/* Data Register */
#define PINL_DR                     (* (reg32 *) PINL__DR)
/* Input Buffer Disable Override */
#define PINL_INP_DIS                (* (reg32 *) PINL__PC2)

/* Interrupt configuration Registers */
#define PINL_INTCFG                 (* (reg32 *) PINL__INTCFG)
#define PINL_INTSTAT                (* (reg32 *) PINL__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PINL_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PINL__SIO)
    #define PINL_SIO_REG            (* (reg32 *) PINL__SIO)
#endif /* (PINL__SIO_CFG) */

/* USBIO registers */
#if !defined(PINL__PC) && (CY_PSOC4_4200L)
    #define PINL_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PINL_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PINL_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PINL_DRIVE_MODE_SHIFT       (0x00u)
#define PINL_DRIVE_MODE_MASK        (0x07u << PINL_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PINL_H */


/* [] END OF FILE */
