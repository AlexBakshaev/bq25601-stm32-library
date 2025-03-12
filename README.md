# BQ25601 Library for STM32 with interrupt callback
### IC:  BQ25601RTWR
### MCU: STM32L072RZT6
### Callback in bq25601.c
## Functions:
- uint8_t bq25601_read_register(uint8_t register_number)
- void bq25601_write_register(uint8_t register_number, uint8_t data)
- uint8_t bq25601_read_bit(uint8_t register_number, uint8_t bit_mask)
- void bq25601_write_bit(uint8_t register_number, uint8_t bit_mask, uint8_t bit_val)
- void bq25601_read_all_registers(BQ25601_Data_TypeDef *regs_data)
- uint8_t bq25601_get_vbus_status(void)
- uint8_t bq25601_get_chrg_status(void)
- uint8_t bq25601_get_ntc_fault(void)
- uint8_t bq25601_get_device_pn(void)
- uint8_t bq25601_get_device_rev(void)
- uint8_t bq25601_read_qon_pin(void)
- uint8_t bq25601_read_stat_pin(void)
- void bq25601_write_ce_pin(uint8_t temp_ce_pin_val)
- void bq25601_set_charge_current_limit(uint8_t iindpm_4_0)
- void bq25601_set_charge_voltage(uint8_t temp_vreg_4_0)
- void bq25601_reset_registers_to_defaults(void)
- void bq25601_enter_ship_mode(void)
- void bq25601_exit_ship_mode(void)
## About:
- [x] HAL_I2C_Mem_Read & HAL_I2C_Mem_Write
- [ ] CMSIS
## Files:
bq25601.pdf - datasheet