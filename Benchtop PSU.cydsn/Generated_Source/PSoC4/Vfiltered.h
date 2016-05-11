/*******************************************************************************
* File Name: Vfiltered.h  
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

#if !defined(CY_PINS_Vfiltered_H) /* Pins Vfiltered_H */
#define CY_PINS_Vfiltered_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vfiltered_aliases.h"


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
} Vfiltered_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Vfiltered_Read(void);
void    Vfiltered_Write(uint8 value);
uint8   Vfiltered_ReadDataReg(void);
#if defined(Vfiltered__PC) || (CY_PSOC4_4200L) 
    void    Vfiltered_SetDriveMode(uint8 mode);
#endif
void    Vfiltered_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vfiltered_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Vfiltered_Sleep(void); 
void Vfiltered_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Vfiltered__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Vfiltered_DRIVE_MODE_BITS        (3)
    #define Vfiltered_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vfiltered_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Vfiltered_SetDriveMode() function.
         *  @{
         */
        #define Vfiltered_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Vfiltered_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Vfiltered_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Vfiltered_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Vfiltered_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Vfiltered_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Vfiltered_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Vfiltered_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Vfiltered_MASK               Vfiltered__MASK
#define Vfiltered_SHIFT              Vfiltered__SHIFT
#define Vfiltered_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vfiltered_SetInterruptMode() function.
     *  @{
     */
        #define Vfiltered_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Vfiltered_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Vfiltered_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Vfiltered_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Vfiltered__SIO)
    #define Vfiltered_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Vfiltered__PC) && (CY_PSOC4_4200L)
    #define Vfiltered_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Vfiltered_USBIO_DISABLE              ((uint32)(~Vfiltered_USBIO_ENABLE))
    #define Vfiltered_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Vfiltered_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Vfiltered_USBIO_ENTER_SLEEP          ((uint32)((1u << Vfiltered_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Vfiltered_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vfiltered_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Vfiltered_USBIO_SUSPEND_SHIFT)))
    #define Vfiltered_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Vfiltered_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vfiltered_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Vfiltered__PC)
    /* Port Configuration */
    #define Vfiltered_PC                 (* (reg32 *) Vfiltered__PC)
#endif
/* Pin State */
#define Vfiltered_PS                     (* (reg32 *) Vfiltered__PS)
/* Data Register */
#define Vfiltered_DR                     (* (reg32 *) Vfiltered__DR)
/* Input Buffer Disable Override */
#define Vfiltered_INP_DIS                (* (reg32 *) Vfiltered__PC2)

/* Interrupt configuration Registers */
#define Vfiltered_INTCFG                 (* (reg32 *) Vfiltered__INTCFG)
#define Vfiltered_INTSTAT                (* (reg32 *) Vfiltered__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Vfiltered_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Vfiltered__SIO)
    #define Vfiltered_SIO_REG            (* (reg32 *) Vfiltered__SIO)
#endif /* (Vfiltered__SIO_CFG) */

/* USBIO registers */
#if !defined(Vfiltered__PC) && (CY_PSOC4_4200L)
    #define Vfiltered_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Vfiltered_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Vfiltered_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Vfiltered_DRIVE_MODE_SHIFT       (0x00u)
#define Vfiltered_DRIVE_MODE_MASK        (0x07u << Vfiltered_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Vfiltered_H */


/* [] END OF FILE */
