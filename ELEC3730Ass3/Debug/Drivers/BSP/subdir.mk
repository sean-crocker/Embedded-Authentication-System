################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/dcmi_ov7670.c \
../Drivers/BSP/ili9325.c \
../Drivers/BSP/openx07v_c_lcd.c \
../Drivers/BSP/sccb.c \
../Drivers/BSP/stm32f4xx_hal_i2c.c \
../Drivers/BSP/touch_panel.c 

OBJS += \
./Drivers/BSP/dcmi_ov7670.o \
./Drivers/BSP/ili9325.o \
./Drivers/BSP/openx07v_c_lcd.o \
./Drivers/BSP/sccb.o \
./Drivers/BSP/stm32f4xx_hal_i2c.o \
./Drivers/BSP/touch_panel.o 

C_DEPS += \
./Drivers/BSP/dcmi_ov7670.d \
./Drivers/BSP/ili9325.d \
./Drivers/BSP/openx07v_c_lcd.d \
./Drivers/BSP/sccb.d \
./Drivers/BSP/stm32f4xx_hal_i2c.d \
./Drivers/BSP/touch_panel.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/%.o Drivers/BSP/%.su Drivers/BSP/%.cyclo: ../Drivers/BSP/%.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/BSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/dcmi_ov7670.cyclo ./Drivers/BSP/dcmi_ov7670.d ./Drivers/BSP/dcmi_ov7670.o ./Drivers/BSP/dcmi_ov7670.su ./Drivers/BSP/ili9325.cyclo ./Drivers/BSP/ili9325.d ./Drivers/BSP/ili9325.o ./Drivers/BSP/ili9325.su ./Drivers/BSP/openx07v_c_lcd.cyclo ./Drivers/BSP/openx07v_c_lcd.d ./Drivers/BSP/openx07v_c_lcd.o ./Drivers/BSP/openx07v_c_lcd.su ./Drivers/BSP/sccb.cyclo ./Drivers/BSP/sccb.d ./Drivers/BSP/sccb.o ./Drivers/BSP/sccb.su ./Drivers/BSP/stm32f4xx_hal_i2c.cyclo ./Drivers/BSP/stm32f4xx_hal_i2c.d ./Drivers/BSP/stm32f4xx_hal_i2c.o ./Drivers/BSP/stm32f4xx_hal_i2c.su ./Drivers/BSP/touch_panel.cyclo ./Drivers/BSP/touch_panel.d ./Drivers/BSP/touch_panel.o ./Drivers/BSP/touch_panel.su

.PHONY: clean-Drivers-2f-BSP

