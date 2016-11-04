################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/DSP/arm_copy_q15.c \
../Src/DSP/arm_mat_mult_q15.c \
../Src/DSP/arm_sin_cos_q31.c \
../Src/DSP/arm_sqrt_q15.c \
../Src/DSP/arm_sqrt_q31.c \
../Src/DSP/common_tables.c 

OBJS += \
./Src/DSP/arm_copy_q15.o \
./Src/DSP/arm_mat_mult_q15.o \
./Src/DSP/arm_sin_cos_q31.o \
./Src/DSP/arm_sqrt_q15.o \
./Src/DSP/arm_sqrt_q31.o \
./Src/DSP/common_tables.o 

C_DEPS += \
./Src/DSP/arm_copy_q15.d \
./Src/DSP/arm_mat_mult_q15.d \
./Src/DSP/arm_sin_cos_q31.d \
./Src/DSP/arm_sqrt_q15.d \
./Src/DSP/arm_sqrt_q31.d \
./Src/DSP/common_tables.d 


# Each subdirectory must supply rules for building sources it contributes
Src/DSP/%.o: ../Src/DSP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F103xB -DARM_MATH_CM3 -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Inc" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/CMSIS/Include" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/CMSIS/Include" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Src" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Src/DSP" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/DTUser/Documents/GitHub/ESPCM3drone/Programacion/WorkSpace/CM3drone/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


