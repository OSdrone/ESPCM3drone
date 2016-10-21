################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Funciones/FuncionAHRS.c \
../Src/Funciones/FuncionControl.c \
../Src/Funciones/FuncionIMU.c \
../Src/Funciones/Funciones_RTOS.c 

OBJS += \
./Src/Funciones/FuncionAHRS.o \
./Src/Funciones/FuncionControl.o \
./Src/Funciones/FuncionIMU.o \
./Src/Funciones/Funciones_RTOS.o 

C_DEPS += \
./Src/Funciones/FuncionAHRS.d \
./Src/Funciones/FuncionControl.d \
./Src/Funciones/FuncionIMU.d \
./Src/Funciones/Funciones_RTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Funciones/%.o: ../Src/Funciones/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F103xB -DARM_MATH_CM3 -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Inc" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Drivers/CMSIS/Include" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/DTUser/Desktop/ESPCM3drone-master/Programacion/WorkSpace/CM3drone/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


