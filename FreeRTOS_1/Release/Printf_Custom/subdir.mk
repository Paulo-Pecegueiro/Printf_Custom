################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Printf_Custom/printf_custom.c 

OBJS += \
./Printf_Custom/printf_custom.o 

C_DEPS += \
./Printf_Custom/printf_custom.d 


# Each subdirectory must supply rules for building sources it contributes
Printf_Custom/printf_custom.o: ../Printf_Custom/printf_custom.c Printf_Custom/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"C:/Users/paulo/STM32CubeIDE/Workspace FreeRTOS/FreeRTOS_1/Printf_Custom" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Printf_Custom/printf_custom.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

