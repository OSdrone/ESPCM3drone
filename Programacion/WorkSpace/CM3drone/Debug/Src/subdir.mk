################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/AHRS.c \
../Src/Constantes.c \
../Src/ServidoresVariables.c \
../Src/adc.c \
../Src/crc.c \
../Src/dma.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/iwdg.c \
../Src/main.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/tim.c \
../Src/usart.c \
../Src/usb_device.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c \
../Src/usbd_dfu_if.c 

OBJS += \
./Src/AHRS.o \
./Src/Constantes.o \
./Src/ServidoresVariables.o \
./Src/adc.o \
./Src/crc.o \
./Src/dma.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/iwdg.o \
./Src/main.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/tim.o \
./Src/usart.o \
./Src/usb_device.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o \
./Src/usbd_dfu_if.o 

C_DEPS += \
./Src/AHRS.d \
./Src/Constantes.d \
./Src/ServidoresVariables.d \
./Src/adc.d \
./Src/crc.d \
./Src/dma.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/iwdg.d \
./Src/main.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/tim.d \
./Src/usart.d \
./Src/usb_device.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d \
./Src/usbd_dfu_if.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F103xB -DARM_MATH_CM3 -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Inc" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/CMSIS/Include" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/Ruben/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


