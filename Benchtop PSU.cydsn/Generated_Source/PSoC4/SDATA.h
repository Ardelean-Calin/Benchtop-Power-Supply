/*******************************************************************************
* File Name: SDATA.h  
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

#if !defined(CY_PINS_SDATA_H) /* Pins SDATA_H */
#define CY_PINS_SDATA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SDATA_aliases.h"


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
} SDATA_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SDATA_Read(void);
void    SDATA_Write(uint8 value);
uint8   SDATA_ReadDataReg(void);
#if defined(SDATA__PC) || (CY_PSOC4_4200L) 
    void    SDATA_SetDriveMode(uint8 mode);
#endif
void    SDATA_SetInterruptMode(uint16 position, uint16 mode);
uint8   SDATA_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SDATA_Sleep(void); 
void SDATA_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SDATA__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SDATA_DRIVE_MODE_BITS        (3)
    #define SDATA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SDATA_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SDATA_SetDriveMode() function.
         *  @{
         */
        #define SDATA_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SDATA_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SDATA_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SDATA_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SDATA_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SDATA_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SDATA_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SDATA_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SDATA_MASK               SDATA__MASK
#define SDATA_SHIFT              SDATA__SHIFT
#define SDATA_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SDATA_SetInterruptMode() function.
     *  @{
     */
        #define SDATA_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SDATA_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SDATA_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SDATA_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SDATA__SIO)
    #define SDATA_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SDATA__PC) && (CY_PSOC4_4200L)
    #define SDATA_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SDATA_USBIO_DISABLE              ((uint32)(~SDATA_USBIO_ENABLE))
    #define SDATA_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SDATA_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SDATA_USBIO_ENTER_SLEEP          ((uint32)((1u << SDATA_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SDATA_USBIO_SUSPEND_DEL_SHIFT)))
    #define SDATA_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SDATA_USBIO_SUSPEND_SHIFT)))
    #define SDATA_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SDATA_USBIO_SUSPEND_DEL_SHIFT)))
    #define SDATA_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SDATA__PC)
    /* Port Configuration */
    #define SDATA_PC                 (* (reg32 *) SDATA__PC)
#endif
/* Pin State */
#define SDATA_PS                     (* (reg32 *) SDATA__PS)
/* Data Register */
#define SDATA_DR                     (* (reg32 *) SDATA__DR)
/* Input Buffer Disable Override */
#define SDATA_INP_DIS                (* (reg32 *) SDATA__PC2)

/* Interrupt configuration Registers */
#define SDATA_INTCFG                 (* (reg32 *) SDATA__INTCFG)
#define SDATA_INTSTAT                (* (reg32 *) SDATA__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SDATA_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SDATA__SIO)
    #define SDATA_SIO_REG            (* (reg32 *) SDATA__SIO)
#endif /* (SDATA__SIO_CFG) */

/* USBIO registers */
#if !defined(SDATA__PC) && (CY_PSOC4_4200L)
    #define SDATA_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SDATA_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SDATA_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SDATA_DRIVE_MODE_SHIFT       (0x00u)
#define SDATA_DRIVE_MODE_MASK        (0x07u << SDATA_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SDATA_H */


/* [] END OF FILE */
