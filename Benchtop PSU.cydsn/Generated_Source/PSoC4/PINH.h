/*******************************************************************************
* File Name: PINH.h  
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

#if !defined(CY_PINS_PINH_H) /* Pins PINH_H */
#define CY_PINS_PINH_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PINH_aliases.h"


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
} PINH_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PINH_Read(void);
void    PINH_Write(uint8 value);
uint8   PINH_ReadDataReg(void);
#if defined(PINH__PC) || (CY_PSOC4_4200L) 
    void    PINH_SetDriveMode(uint8 mode);
#endif
void    PINH_SetInterruptMode(uint16 position, uint16 mode);
uint8   PINH_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PINH_Sleep(void); 
void PINH_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PINH__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PINH_DRIVE_MODE_BITS        (3)
    #define PINH_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PINH_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PINH_SetDriveMode() function.
         *  @{
         */
        #define PINH_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PINH_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PINH_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PINH_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PINH_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PINH_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PINH_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PINH_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PINH_MASK               PINH__MASK
#define PINH_SHIFT              PINH__SHIFT
#define PINH_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PINH_SetInterruptMode() function.
     *  @{
     */
        #define PINH_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PINH_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PINH_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PINH_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PINH__SIO)
    #define PINH_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PINH__PC) && (CY_PSOC4_4200L)
    #define PINH_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PINH_USBIO_DISABLE              ((uint32)(~PINH_USBIO_ENABLE))
    #define PINH_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PINH_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PINH_USBIO_ENTER_SLEEP          ((uint32)((1u << PINH_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PINH_USBIO_SUSPEND_DEL_SHIFT)))
    #define PINH_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PINH_USBIO_SUSPEND_SHIFT)))
    #define PINH_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PINH_USBIO_SUSPEND_DEL_SHIFT)))
    #define PINH_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PINH__PC)
    /* Port Configuration */
    #define PINH_PC                 (* (reg32 *) PINH__PC)
#endif
/* Pin State */
#define PINH_PS                     (* (reg32 *) PINH__PS)
/* Data Register */
#define PINH_DR                     (* (reg32 *) PINH__DR)
/* Input Buffer Disable Override */
#define PINH_INP_DIS                (* (reg32 *) PINH__PC2)

/* Interrupt configuration Registers */
#define PINH_INTCFG                 (* (reg32 *) PINH__INTCFG)
#define PINH_INTSTAT                (* (reg32 *) PINH__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PINH_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PINH__SIO)
    #define PINH_SIO_REG            (* (reg32 *) PINH__SIO)
#endif /* (PINH__SIO_CFG) */

/* USBIO registers */
#if !defined(PINH__PC) && (CY_PSOC4_4200L)
    #define PINH_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PINH_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PINH_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PINH_DRIVE_MODE_SHIFT       (0x00u)
#define PINH_DRIVE_MODE_MASK        (0x07u << PINH_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PINH_H */


/* [] END OF FILE */
