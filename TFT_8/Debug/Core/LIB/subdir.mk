################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LIB/BUS.c \
../Core/LIB/globals.c \
../Core/LIB/touch_gtxxxx.c \
../Core/LIB/touch_gtxxxx_bsp.c 

C_DEPS += \
./Core/LIB/BUS.d \
./Core/LIB/globals.d \
./Core/LIB/touch_gtxxxx.d \
./Core/LIB/touch_gtxxxx_bsp.d 

OBJS += \
./Core/LIB/BUS.o \
./Core/LIB/globals.o \
./Core/LIB/touch_gtxxxx.o \
./Core/LIB/touch_gtxxxx_bsp.o 


# Each subdirectory must supply rules for building sources it contributes
Core/LIB/%.o Core/LIB/%.su: ../Core/LIB/%.c Core/LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../USB_HOST/App -I../USB_HOST/Target -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-LIB

clean-Core-2f-LIB:
	-$(RM) ./Core/LIB/BUS.d ./Core/LIB/BUS.o ./Core/LIB/BUS.su ./Core/LIB/globals.d ./Core/LIB/globals.o ./Core/LIB/globals.su ./Core/LIB/touch_gtxxxx.d ./Core/LIB/touch_gtxxxx.o ./Core/LIB/touch_gtxxxx.su ./Core/LIB/touch_gtxxxx_bsp.d ./Core/LIB/touch_gtxxxx_bsp.o ./Core/LIB/touch_gtxxxx_bsp.su

.PHONY: clean-Core-2f-LIB

