################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Ass-03-CameraTask.c \
../Core/Src/Ass-03-ControlTask.c \
../Core/Src/Ass-03-KeypadTask.c \
../Core/Src/Ass-03-LCDTask.c \
../Core/Src/Ass-03-MessageTimer.c \
../Core/Src/Ass-03-SDTask.c \
../Core/Src/Ass-03-TouchPanelTask.c \
../Core/Src/dcmi.c \
../Core/Src/dma.c \
../Core/Src/freertos.c \
../Core/Src/fsmc.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/sdio.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/Ass-03-CameraTask.o \
./Core/Src/Ass-03-ControlTask.o \
./Core/Src/Ass-03-KeypadTask.o \
./Core/Src/Ass-03-LCDTask.o \
./Core/Src/Ass-03-MessageTimer.o \
./Core/Src/Ass-03-SDTask.o \
./Core/Src/Ass-03-TouchPanelTask.o \
./Core/Src/dcmi.o \
./Core/Src/dma.o \
./Core/Src/freertos.o \
./Core/Src/fsmc.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/sdio.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/Ass-03-CameraTask.d \
./Core/Src/Ass-03-ControlTask.d \
./Core/Src/Ass-03-KeypadTask.d \
./Core/Src/Ass-03-LCDTask.d \
./Core/Src/Ass-03-MessageTimer.d \
./Core/Src/Ass-03-SDTask.d \
./Core/Src/Ass-03-TouchPanelTask.d \
./Core/Src/dcmi.d \
./Core/Src/dma.d \
./Core/Src/freertos.d \
./Core/Src/fsmc.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/sdio.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/BSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Ass-03-CameraTask.cyclo ./Core/Src/Ass-03-CameraTask.d ./Core/Src/Ass-03-CameraTask.o ./Core/Src/Ass-03-CameraTask.su ./Core/Src/Ass-03-ControlTask.cyclo ./Core/Src/Ass-03-ControlTask.d ./Core/Src/Ass-03-ControlTask.o ./Core/Src/Ass-03-ControlTask.su ./Core/Src/Ass-03-KeypadTask.cyclo ./Core/Src/Ass-03-KeypadTask.d ./Core/Src/Ass-03-KeypadTask.o ./Core/Src/Ass-03-KeypadTask.su ./Core/Src/Ass-03-LCDTask.cyclo ./Core/Src/Ass-03-LCDTask.d ./Core/Src/Ass-03-LCDTask.o ./Core/Src/Ass-03-LCDTask.su ./Core/Src/Ass-03-MessageTimer.cyclo ./Core/Src/Ass-03-MessageTimer.d ./Core/Src/Ass-03-MessageTimer.o ./Core/Src/Ass-03-MessageTimer.su ./Core/Src/Ass-03-SDTask.cyclo ./Core/Src/Ass-03-SDTask.d ./Core/Src/Ass-03-SDTask.o ./Core/Src/Ass-03-SDTask.su ./Core/Src/Ass-03-TouchPanelTask.cyclo ./Core/Src/Ass-03-TouchPanelTask.d ./Core/Src/Ass-03-TouchPanelTask.o ./Core/Src/Ass-03-TouchPanelTask.su ./Core/Src/dcmi.cyclo ./Core/Src/dcmi.d ./Core/Src/dcmi.o ./Core/Src/dcmi.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/fsmc.cyclo ./Core/Src/fsmc.d ./Core/Src/fsmc.o ./Core/Src/fsmc.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/sdio.cyclo ./Core/Src/sdio.d ./Core/Src/sdio.o ./Core/Src/sdio.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

