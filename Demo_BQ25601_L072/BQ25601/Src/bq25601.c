/*
 * bq25601.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Alex Bakshaev (aka Дрочеслав in Blue Archive)
 */
#include "bq25601.h"

// Includes:
#include "main.h"
#include <stdio.h>
#include "stm32l0xx_hal_i2c.h"

// External:
extern I2C_HandleTypeDef hi2c1;

// Defines
#define ENABLE_INT_PIN_CALLBACK
#define BQ25601_HI2C hi2c1

#define BQ25601_USE_HAL
//#define BQ25601_USE_CMSIS

// MCU Parameters:
// INT
#define BQ25601_INT_PIN CHG_INT_Pin
// QON
#define BQ25601_QON_GPIO_PORT CHG_QON_GPIO_Port
#define BQ25601_QON_PIN	CHG_QON_Pin
// STAT
#define BQ25601_STAT_GPIO_PORT CHG_STAT_GPIO_Port
#define BQ25601_STAT_PIN CHG_STAT_Pin
// CE
#define BQ25601_CE_GPIO_PORT CHG_CE_GPIO_Port
#define BQ25601_CE_PIN CHG_CE_Pin

// Interrupt callback:
#ifdef ENABLE_INT_PIN_CALLBACK

// External data:
extern BQ25601_Data_TypeDef bq25601_registers;
extern uint8_t bq25601_vbus;
extern uint8_t bq25601_chg_current;
extern uint8_t bq25601_ntc;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin == BQ25601_INT_PIN) {
		// Write your code for interrupts with
		bq25601_read_all_registers(&bq25601_registers);
		bq25601_vbus = bq25601_get_vbus_status();
		bq25601_ntc = bq25601_get_ntc_fault();

		if((bq25601_vbus != BQ25601_NO_INPUT) &&(bq25601_ntc == BQ25601_NTC_NORMAL)) {
			bq25601_set_charge_current_limit(bq25601_chg_current);
		}
		else if(bq25601_ntc != BQ25601_NTC_NORMAL) {
			bq25601_write_ce_pin(1);
		}
	}
}
#endif

/*-------------------- F U N C T I O N S --------------------*/
/*-------------------- G E N E R A L --------------------*/
// Base function for read register
uint8_t bq25601_read_register(uint8_t register_number) {
	uint8_t temp_reg_data = 0;
#ifdef BQ25601_USE_HAL
	HAL_I2C_Mem_Read(&BQ25601_HI2C, BQ25601_I2C_ADDRESS<<1, register_number, 1, &temp_reg_data, 1, HAL_MAX_DELAY);
#elif defined(BQ25601_USE_CMSIS)
#endif
	return temp_reg_data;
}

// Base function for write register
void bq25601_write_register(uint8_t register_number, uint8_t data) {
#ifdef BQ25601_USE_HAL
	HAL_I2C_Mem_Write(&BQ25601_HI2C, BQ25601_I2C_ADDRESS<<1, register_number, 1, &data, 1, HAL_MAX_DELAY);
#elif defined(BQ25601_USE_CMSIS)
#endif
}

// Base function for read bit register, returns bit with offset
uint8_t bq25601_read_bit(uint8_t register_number, uint8_t bit_mask) {
	uint8_t temp_reg_data = 0;
#ifdef BQ25601_USE_HAL
	temp_reg_data = bq25601_read_register(register_number);
#elif defined(BQ25601_USE_CMSIS)
#endif
	temp_reg_data &= bit_mask;
	return temp_reg_data;
}

// Base function for write bit in register
void bq25601_write_bit(uint8_t register_number, uint8_t bit_mask, uint8_t bit_val) {
	uint8_t temp_reg_data = 0;
#ifdef BQ25601_USE_HAL
	temp_reg_data = bq25601_read_register(register_number);
#elif defined(BQ25601_USE_CMSIS)
#endif
	if(bit_val) {
		temp_reg_data |= bit_mask;
	}
	else {
		temp_reg_data &= (~bit_mask);
	}
#ifdef BQ25601_USE_HAL
	bq25601_write_register(register_number, temp_reg_data);
#elif defined(BQ25601_USE_CMSIS)
#endif
}

/*-------------------- R E A D --------------------*/
// Reads all registers, fills BQ25601_Data_TypeDef
void bq25601_read_all_registers(BQ25601_Data_TypeDef *regs_data) {
	regs_data->BQ25601_REG00 = bq25601_read_register(BQ25601_REG00_ADDRESS);
	regs_data->BQ25601_REG01 = bq25601_read_register(BQ25601_REG01_ADDRESS);
	regs_data->BQ25601_REG02 = bq25601_read_register(BQ25601_REG02_ADDRESS);
	regs_data->BQ25601_REG03 = bq25601_read_register(BQ25601_REG03_ADDRESS);
	regs_data->BQ25601_REG04 = bq25601_read_register(BQ25601_REG04_ADDRESS);
	regs_data->BQ25601_REG05 = bq25601_read_register(BQ25601_REG05_ADDRESS);
	regs_data->BQ25601_REG06 = bq25601_read_register(BQ25601_REG06_ADDRESS);
	regs_data->BQ25601_REG07 = bq25601_read_register(BQ25601_REG07_ADDRESS);
	regs_data->BQ25601_REG08 = bq25601_read_register(BQ25601_REG08_ADDRESS);
	regs_data->BQ25601_REG09 = bq25601_read_register(BQ25601_REG09_ADDRESS);
	regs_data->BQ25601_REG0A = bq25601_read_register(BQ25601_REG0A_ADDRESS);
	regs_data->BQ25601_REG0B = bq25601_read_register(BQ25601_REG0B_ADDRESS);
}

// Returns VBUS_STAT 2 1 0 like 0bxxx
uint8_t bq25601_get_vbus_status(void) {
	uint8_t reg08_data = 0;
	reg08_data = bq25601_read_register(BQ25601_REG08_ADDRESS);
	return (reg08_data >> 5);
}

// Returns CHRG_STAT 1 0 like 0bxx
uint8_t bq25601_get_chrg_status(void) {
	uint8_t reg08_data = 0;
	reg08_data = bq25601_read_register(BQ25601_REG08_ADDRESS);
	return ((reg08_data & 0b00011000)>>3);
}

// Returns NTC_FAULT 2 1 0 like 0bxxx
uint8_t bq25601_get_ntc_fault(void) {
	uint8_t reg_09_data = bq25601_read_register(BQ25601_REG09_ADDRESS);
	reg_09_data &= (BQ25601_REG09_MSK_NTC_FAULT_2 | BQ25601_REG09_MSK_NTC_FAULT_1 | BQ25601_REG09_MSK_NTC_FAULT_0);
	return reg_09_data;
}

// Returns device part number (id) like 0bxxx
uint8_t bq25601_get_device_pn(void) {
	uint8_t reg0b_data = 0;
	reg0b_data = bq25601_read_register(BQ25601_REG0B_ADDRESS);
	return ((reg0b_data & 0b0111100)>>3);
}

//Returns device revision like 0bxx
uint8_t bq25601_get_device_rev(void) {
	uint8_t reg0b_data = 0;
	reg0b_data = bq25601_read_register(BQ25601_REG0B_ADDRESS);
	reg0b_data &= (BQ25601_REG0B_MSK_DEV_REV_1 | BQ25601_REG0B_MSK_DEV_REV_0);
	return reg0b_data;
}

/*-------------------- G P I O s --------------------*/
// Read QON pin
uint8_t bq25601_read_qon_pin(void) {
	uint8_t temp_qon_pin_data;
	temp_qon_pin_data = HAL_GPIO_ReadPin(BQ25601_QON_GPIO_PORT, BQ25601_QON_PIN);
	return temp_qon_pin_data;
}

// Read STAT pin
uint8_t bq25601_read_stat_pin(void) {
	uint8_t temp_stat_pin_data;
	temp_stat_pin_data = HAL_GPIO_ReadPin(BQ25601_STAT_GPIO_PORT, BQ25601_STAT_PIN);
	return temp_stat_pin_data;
}

// Write CE pin
void bq25601_write_ce_pin(uint8_t temp_ce_pin_val) {
	HAL_GPIO_WritePin(BQ25601_CE_GPIO_PORT, BQ25601_CE_PIN, temp_ce_pin_val);
}

/*-------------------- W R I T E --------------------*/
// Set charge current limit using masks: BQ25601_REG00_MSK_IINDPM
void bq25601_set_charge_current_limit(uint8_t iindpm_4_0) {
	uint8_t temp_reg_00_data = 0;
	temp_reg_00_data = bq25601_read_register(BQ25601_REG00_ADDRESS);
	temp_reg_00_data &= (BQ25601_REG00_MSK_EN_HIZ | BQ25601_REG00_MSK_EN_ICHG_MON_1 | BQ25601_REG00_MSK_EN_ICHG_MON_0);
	temp_reg_00_data |= iindpm_4_0;
	bq25601_write_register(BQ25601_REG00_ADDRESS, temp_reg_00_data);
}

// Set charge voltage using masks: BQ25601_REG04_MSK_VREG
void bq25601_set_charge_voltage(uint8_t temp_vreg_4_0) {
	uint8_t temp_reg_04_data = 0;
	temp_reg_04_data = bq25601_read_register(BQ25601_REG04_ADDRESS);
	temp_reg_04_data &= (BQ25601_REG04_MSK_TOPOFF_TIMER_1 | BQ25601_REG04_MSK_TOPOFF_TIMER_0 | BQ25601_REG04_MSK_VRECHG);
	temp_reg_04_data |= temp_vreg_4_0;
	bq25601_write_register(BQ25601_REG04_ADDRESS, temp_reg_04_data);
}

// Resets registers to defaults
void bq25601_reset_registers_to_defaults(void) {
	uint8_t temp_reg_0b_data = 0;
	temp_reg_0b_data = bq25601_read_register(BQ25601_REG0B_ADDRESS);
	bq25601_write_register(BQ25601_REG0B_ADDRESS, temp_reg_0b_data | BQ25601_REG0B_MSK_REG_RST);
}

// Enter ship mode (BATFET_DIS) - turn off VSYS
void bq25601_enter_ship_mode(void) {
	bq25601_write_bit(BQ25601_REG07_ADDRESS, BQ25601_REG07_MSK_BATFET_DIS, 1);
}

// Exit ship mode (BATFET_DIS) - turn on VSYS
void bq25601_exit_ship_mode(void) {
	bq25601_write_bit(BQ25601_REG07_ADDRESS, BQ25601_REG07_MSK_BATFET_DIS, 0);
}
