/*
 * bq25601.h
 *
 *  Created on: Mar 10, 2025
 *      Author: Alex Bakshaev (aka Дрочеслав in Blue Archive)
 */
#ifndef INC_BQ25601_H_
#define INC_BQ25601_H_

// Includes
#include "stdint.h"

// I2C Address (without offset)
#define BQ25601_I2C_ADDRESS 0x6B

/*-------------------- S T R U C T U R E --------------------*/
typedef struct {
	uint8_t BQ25601_REG00;
	uint8_t BQ25601_REG01;
	uint8_t BQ25601_REG02;
	uint8_t BQ25601_REG03;
	uint8_t BQ25601_REG04;
	uint8_t BQ25601_REG05;
	uint8_t BQ25601_REG06;
	uint8_t BQ25601_REG07;
	uint8_t BQ25601_REG08;
	uint8_t BQ25601_REG09;
	uint8_t BQ25601_REG0A;
	uint8_t BQ25601_REG0B;
}BQ25601_Data_TypeDef;

/*-------------------- S T A T U S E S --------------------*/
// VBUS
typedef enum {
	BQ25601_NO_INPUT = 0b000,
	BQ25601_USB_HOST_SDP_500MA = 0b001,
	BQ25601_ADAPTER_2_4_A = 0b011,
	BQ25601_OTG = 0b111
}BQ25601_VBUS_STAT_TypeDef;
// Charge
typedef enum {
	BQ25601_NOT_CHARGING = 0b00,
	BQ25601_PRE_CHARGE = 0b01,
	BQ25601_FAST_CHARGING = 0b10,
	BQ25601_CHARGE_TERMINATION = 0b11
}BQ25601_CHRG_STAT_TypeDef;
// NTC
typedef enum {
	BQ25601_NTC_NORMAL = 0b000,
	BQ25601_NTC_WARM = 0b010,
	BQ25601_NTC_COOL = 0b011,
	BQ25601_NTC_HOT = 0b110
}BQ25601_NTC_FAULT_TypeDef;
/*
 *  Ps BQ25601_VBUS_STAT_TypeDef & BQ25601_CHRG_STAT_TypeDef & BQ25601_NTC_FAULT_TypeDef not in BQ25601_Data_TypeDef, because if BQ25601_Data_TypeDef will includes these enums it must aslo include all bit states and etc
 */

/*-------------------- R E G I S T E R S --------------------*/
#define BQ25601_REG00_ADDRESS 0x00
#define BQ25601_REG01_ADDRESS 0x01
#define BQ25601_REG02_ADDRESS 0x02
#define BQ25601_REG03_ADDRESS 0x03
#define BQ25601_REG04_ADDRESS 0x04
#define BQ25601_REG05_ADDRESS 0x05
#define BQ25601_REG06_ADDRESS 0x06
#define BQ25601_REG07_ADDRESS 0x07
#define BQ25601_REG08_ADDRESS 0x08
#define BQ25601_REG09_ADDRESS 0x09
#define BQ25601_REG0A_ADDRESS 0x0A
#define BQ25601_REG0B_ADDRESS 0x0B

// REG00:
#define BQ25601_REG00_MSK_EN_HIZ        128
#define BQ25601_REG00_MSK_EN_ICHG_MON_1 64
#define BQ25601_REG00_MSK_EN_ICHG_MON_0 32
#define BQ25601_REG00_MSK_IINDPM_4_1600 16
#define BQ25601_REG00_MSK_IINDPM_3_800  8
#define BQ25601_REG00_MSK_IINDPM_2_400  4
#define BQ25601_REG00_MSK_IINDPM_1_200  2
#define BQ25601_REG00_MSK_IINDPM_0_100  1
// REG01:
#define BQ25601_REG01_MSK_PFM_DIS       128
#define BQ25601_REG01_MSK_WD_RST        64
#define BQ25601_REG01_MSK_OTG_CONFIG    32
#define BQ25601_REG01_MSK_CHG_CONFIG    16
#define BQ25601_REG01_MSK_SYS_MIN_2     8
#define BQ25601_REG01_MSK_SYS_MIN_1     4
#define BQ25601_REG01_MSK_SYS_MIN_0     2
#define BQ25601_REG01_MSK_MIN_VBAT_SEL  1
// REG02:
#define BQ25601_REG02_MSK_BOOST_LIM     128
#define BQ25601_REG02_MSK_Q1_FULLON     64
#define BQ25601_REG02_MSK_ICHG_5        32
#define BQ25601_REG02_MSK_ICHG_4        16
#define BQ25601_REG02_MSK_ICHG_3        8
#define BQ25601_REG02_MSK_ICHG_2        4
#define BQ25601_REG02_MSK_ICHG_1        2
#define BQ25601_REG02_MSK_ICHG_0        1
// REG03:
#define BQ25601_REG03_MSK_IPRECHG_3     128
#define BQ25601_REG03_MSK_IPRECHG_2     64
#define BQ25601_REG03_MSK_IPRECHG_1     32
#define BQ25601_REG03_MSK_IPRECHG_0     16
#define BQ25601_REG03_MSK_ITERM_3       8
#define BQ25601_REG03_MSK_ITERM_2       4
#define BQ25601_REG03_MSK_ITERM_1       2
#define BQ25601_REG03_MSK_ITERM_0       1
// REG04:
#define BQ25601_REG04_MSK_VREG_4         128
#define BQ25601_REG04_MSK_VREG_3         64
#define BQ25601_REG04_MSK_VREG_2         32
#define BQ25601_REG04_MSK_VREG_1         16
#define BQ25601_REG04_MSK_VREG_0         8
#define BQ25601_REG04_MSK_TOPOFF_TIMER_1 4
#define BQ25601_REG04_MSK_TOPOFF_TIMER_0 2
#define BQ25601_REG04_MSK_VRECHG         1
// REG05:
#define BQ25601_REG05_MSK_EN_TERM       128
#define BQ25601_REG05_MSK_RESERVED      64
#define BQ25601_REG05_MSK_WATCHDOG_1    32
#define BQ25601_REG05_MSK_WATCHDOG_0    16
#define BQ25601_REG05_MSK_EN_TIMER      8
#define BQ25601_REG05_MSK_CHG_TIMER     4
#define BQ25601_REG05_MSK_TREG          2
#define BQ25601_REG05_MSK_JEITA_ISET    1
// REG06:
#define BQ25601_REG06_MSK_OVP_1         128
#define BQ25601_REG06_MSK_OVP_0         64
#define BQ25601_REG06_MSK_BOOSTV_1      32
#define BQ25601_REG06_MSK_BOOSTV_0      16
#define BQ25601_REG06_MSK_VINDPM_3      8
#define BQ25601_REG06_MSK_VINDPM_2      4
#define BQ25601_REG06_MSK_VINDPM_1      2
#define BQ25601_REG06_MSK_VINDPM_0      1
// REG07:
#define BQ25601_REG07_MSK_IINDET_EN     	128
#define BQ25601_REG07_MSK_TMR2X_EN      	64
#define BQ25601_REG07_MSK_BATFET_DIS    	32
#define BQ25601_REG07_MSK_JEITA_VSET    	16
#define BQ25601_REG07_MSK_BATFET_DLY    	8
#define BQ25601_REG07_MSK_BATFET_RST_EN 	4
#define BQ25601_REG07_MSK_VDPM_BAT_TRACK_1  2
#define BQ25601_REG07_MSK_VDPM_BAT_TRACK_0  1
// REG08:
#define BQ25601_REG08_MSK_VBUS_STAT_2   128
#define BQ25601_REG08_MSK_VBUS_STAT_1   64
#define BQ25601_REG08_MSK_VBUS_STAT_0   32
#define BQ25601_REG08_MSK_CHRG_STAT_1   16
#define BQ25601_REG08_MSK_CHRG_STAT_0   8
#define BQ25601_REG08_MSK_PG_STAT       4
#define BQ25601_REG08_MSK_THERM_STAT    2
#define BQ25601_REG08_MSK_VSYS_STAT     1
// REG09:
#define BQ25601_REG09_MSK_WATCHDOG_FAULT 128
#define BQ25601_REG09_MSK_BOOST_FAULT    64
#define BQ25601_REG09_MSK_CHRG_FAULT_1   32
#define BQ25601_REG09_MSK_CHRG_FAULT_0   16
#define BQ25601_REG09_MSK_BAT_FAULT      8
#define BQ25601_REG09_MSK_NTC_FAULT_2    4
#define BQ25601_REG09_MSK_NTC_FAULT_1    2
#define BQ25601_REG09_MSK_NTC_FAULT_0    1
// REG0A:
#define BQ25601_REG0A_MSK_VBUS_GD       	128
#define BQ25601_REG0A_MSK_VINDPM_STAT   	64
#define BQ25601_REG0A_MSK_IINDPM_STAT   	32
#define BQ25601_REG0A_MSK_RESERVED      	16
#define BQ25601_REG0A_MSK_TOPOFF_ACTIVE 	8
#define BQ25601_REG0A_MSK_ACOV_STAT     	4
#define BQ25601_REG0A_MSK_VINDPM_INT_MASK   2
#define BQ25601_REG0A_MSK_IINDPM_INT_MASK   1
// REG0B:
#define BQ25601_REG0B_MSK_REG_RST       128
#define BQ25601_REG0B_MSK_PN_3          64
#define BQ25601_REG0B_MSK_PN_2          32
#define BQ25601_REG0B_MSK_PN_1          16
#define BQ25601_REG0B_MSK_PN_0          8
#define BQ25601_REG0B_MSK_RESERVED      4
#define BQ25601_REG0B_MSK_DEV_REV_1     2
#define BQ25601_REG0B_MSK_DEV_REV_0     1

/*-------------------- F U N C T I O N S --------------------*/
// General Functions:
// Base function for read register
uint8_t bq25601_read_register(uint8_t register_number);
// Base function for write register
void bq25601_write_register(uint8_t register_number, uint8_t data);
// Base function for read bit register, returns bit with offset
uint8_t bq25601_read_bit(uint8_t register_number, uint8_t bit_mask);
// Base function for write bit in register
void bq25601_write_bit(uint8_t register_number, uint8_t bit_mask, uint8_t bit_val);

// Read registers:
// Reads all registers, fills BQ25601_Data_TypeDef
void bq25601_read_all_registers(BQ25601_Data_TypeDef *regs_data);
// Returns VBUS_STAT 2 1 0 like 0bxxx
uint8_t bq25601_get_vbus_status(void);
// Returns CHRG_STAT 1 0 like 0bxx
uint8_t bq25601_get_chrg_status(void);
// Returns NTC_FAULT 2 1 0 like 0bxxx
uint8_t bq25601_get_ntc_fault(void);
// Returns device part number (id) like 0bxxx
uint8_t bq25601_get_device_pn(void);
//Returns device revision like 0bxx
uint8_t bq25601_get_device_rev(void);

// GPIOs:
// Read QON pin
uint8_t bq25601_read_qon_pin(void);
// Read STAT pin
uint8_t bq25601_read_stat_pin(void);
// Write CE pin
void bq25601_write_ce_pin(uint8_t temp_ce_pin_val);

// Write Registers:
// Set charge current limit using masks: BQ25601_REG00_MSK_IINDPM
void bq25601_set_charge_current_limit(uint8_t iindpm_4_0);
// Set charge voltage using masks: BQ25601_REG04_MSK_VREG
void bq25601_set_charge_voltage(uint8_t temp_vreg_4_0);
// Resets registers to defaults
void bq25601_reset_registers_to_defaults(void);
// Enter ship mode (BATFET_DIS) - turn off VSYS
void bq25601_enter_ship_mode(void);
// Exit ship mode (BATFET_DIS) - turn on VSYS
void bq25601_exit_ship_mode(void);
#endif
