################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BQ25601/Src/bq25601.c 

OBJS += \
./BQ25601/Src/bq25601.o 

C_DEPS += \
./BQ25601/Src/bq25601.d 


# Each subdirectory must supply rules for building sources it contributes
BQ25601/Src/%.o BQ25601/Src/%.su BQ25601/Src/%.cyclo: ../BQ25601/Src/%.c BQ25601/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../BQ25601/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BQ25601-2f-Src

clean-BQ25601-2f-Src:
	-$(RM) ./BQ25601/Src/bq25601.cyclo ./BQ25601/Src/bq25601.d ./BQ25601/Src/bq25601.o ./BQ25601/Src/bq25601.su

.PHONY: clean-BQ25601-2f-Src

