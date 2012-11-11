#ifndef _GPIO_HW_H_
#define _GPIO_HW_H_

#include <stdint.h>
#include <Drivers/io.h>

/** @name Register Map
 *
 * Registers of the GPIO peripheral.
 * @{
 */
typedef struct
{
	__IO uint32_t MASK_DATA_LSW_0;			/**< Mask and Data Register LSW, Bank 0 */
	__IO uint32_t MASK_DATA_MSW_0;			/**< Mask and Data Register MSW, Bank 0 */
	__IO uint32_t MASK_DATA_LSW_1;			/**< Mask and Data Register LSW, Bank 1 */
	__IO uint32_t MASK_DATA_MSW_1;			/**< Mask and Data Register MSW, Bank 1 */
	__IO uint32_t MASK_DATA_LSW_2;			/**< Mask and Data Register LSW, Bank 2 */
	__IO uint32_t MASK_DATA_MSW_2;			/**< Mask and Data Register MSW, Bank 2 */
	__IO uint32_t MASK_DATA_LSW_3;			/**< Mask and Data Register LSW, Bank 3 */
	__IO uint32_t MASK_DATA_MSW_3;			/**< Mask and Data Register MSW, Bank 3 */
	__IO uint32_t RESERVED1[0x20/sizeof(uint32_t)];
	__IO uint32_t DATA_0;					/**< Output Data Register, Bank 0 */
	__IO uint32_t DATA_1;					/**< Output Data Register, Bank 1 */
	__IO uint32_t DATA_2;					/**< Output Data Register, Bank 2 */
	__IO uint32_t DATA_3;					/**< Output Data Register, Bank 3 */
	__IO uint32_t RESERVED2[0x10/sizeof(uint32_t)];
	__I  uint32_t DATA_0_RO;				/**< Input Data Register, Bank 0 */
	__I  uint32_t DATA_1_RO;				/**< Input Data Register, Bank 1 */
	__I  uint32_t DATA_2_RO;				/**< Input Data Register, Bank 2 */
	__I  uint32_t DATA_3_RO;				/**< Input Data Register, Bank 3 */
	__IO uint32_t RESERVED3[0x194/sizeof(uint32_t)];
	__IO uint32_t DIRECTION_0;				/**< Direction Mode Register, Bank 0 */
	__IO uint32_t OUTPUT_EN_0;				/**< Output Enable Register, Bank 0 */
	__I  uint32_t INT_MASK_0;				/**< Interrupt Mask Register, Bank 0 */
	__IO uint32_t INT_EN_0;					/**< Interrupt Enable/Unmask Register, Bank 0 */
	__IO uint32_t INT_DIS_0;				/**< Interrupt Disble/Mask Register, Bank 0 */
	__IO uint32_t INT_STAT_0;				/**< Interrupt Status Register, Bank 0 */
	__IO uint32_t INT_TYPE_0;				/**< Interrupt Type Register, Bank 0 */
	__IO uint32_t INT_POLARITY_0;			/**< Interrupt Polarity Register, Bank 0 */
	__IO uint32_t INT_ANY_0;				/**< Interrupt Any Edge Sensitive Register, Bank 0 */
	__IO uint32_t RESERVED4[0x20/sizeof(uint32_t)];
	__IO uint32_t DIRECTION_1;				/**< Direction Mode Register, Bank 1 */
	__IO uint32_t OUTPUT_EN_1;				/**< Output Enable Register, Bank 1 */
	__I  uint32_t INT_MASK_1;				/**< Interrupt Mask Register, Bank 1 */
	__IO uint32_t INT_EN_1;					/**< Interrupt Enable/Unmask Register, Bank 1 */
	__IO uint32_t INT_DIS_1;				/**< Interrupt Disble/Mask Register, Bank 1 */
	__IO uint32_t INT_STAT_1;				/**< Interrupt Status Register, Bank 1 */
	__IO uint32_t INT_TYPE_1;				/**< Interrupt Type Register, Bank 1 */
	__IO uint32_t INT_POLARITY_1;			/**< Interrupt Polarity Register, Bank 1 */
	__IO uint32_t INT_ANY_1;				/**< Interrupt Any Edge Sensitive Register, Bank 1 */
	__IO uint32_t RESERVED5[0x20/sizeof(uint32_t)];
	__IO uint32_t DIRECTION_2;				/**< Direction Mode Register, Bank 2 */
	__IO uint32_t OUTPUT_EN_2;				/**< Output Enable Register, Bank 2 */
	__I  uint32_t INT_MASK_2;				/**< Interrupt Mask Register, Bank 2 */
	__IO uint32_t INT_EN_2;					/**< Interrupt Enable/Unmask Register, Bank 2 */
	__IO uint32_t INT_DIS_2;				/**< Interrupt Disble/Mask Register, Bank 2 */
	__IO uint32_t INT_STAT_2;				/**< Interrupt Status Register, Bank 2 */
	__IO uint32_t INT_TYPE_2;				/**< Interrupt Type Register, Bank 2 */
	__IO uint32_t INT_POLARITY_2;			/**< Interrupt Polarity Register, Bank 2 */
	__IO uint32_t INT_ANY_2;				/**< Interrupt Any Edge Sensitive Register, Bank 2 */
	__IO uint32_t RESERVED6[0x20/sizeof(uint32_t)];
	__IO uint32_t DIRECTION_3;				/**< Direction Mode Register, Bank 3 */
	__IO uint32_t OUTPUT_EN_3;				/**< Output Enable Register, Bank 3 */
	__I  uint32_t INT_MASK_3;				/**< Interrupt Mask Register, Bank 3 */
	__IO uint32_t INT_EN_3;					/**< Interrupt Enable/Unmask Register, Bank 3 */
	__IO uint32_t INT_DIS_3;				/**< Interrupt Disble/Mask Register, Bank 3 */
	__IO uint32_t INT_STAT_3;				/**< Interrupt Status Register, Bank 3 */
	__IO uint32_t INT_TYPE_3;				/**< Interrupt Type Register, Bank 3 */
	__IO uint32_t INT_POLARITY_3;			/**< Interrupt Polarity Register, Bank 3 */
	__IO uint32_t INT_ANY_3;				/**< Interrupt Any Edge Sensitive Register, Bank 3 */
} GPIO_Registers;
/* @} */

#define GPIO_BASE					0xE000A000
#define GPIO						((GPIO_Registers*)GPIO_BASE)

#endif
