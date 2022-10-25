################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/Pump/image_FAN_SB_01.cpp \
../TouchGFX/generated/images/src/Pump/image_FAN_SB_02.cpp \
../TouchGFX/generated/images/src/Pump/image_FAN_SB_03.cpp \
../TouchGFX/generated/images/src/Pump/image_FAN_SB_04.cpp \
../TouchGFX/generated/images/src/Pump/image_PUMP_OS2_02.cpp \
../TouchGFX/generated/images/src/Pump/image_PUMP_OS2_03.cpp \
../TouchGFX/generated/images/src/Pump/image_PUMP_OS2_04.cpp \
../TouchGFX/generated/images/src/Pump/image_PUMP_OS2_05.cpp \
../TouchGFX/generated/images/src/Pump/image_PUMP_OS2_main.cpp 

OBJS += \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_01.o \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_02.o \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_03.o \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_04.o \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_02.o \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_03.o \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_04.o \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_05.o \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_main.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_01.d \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_02.d \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_03.d \
./TouchGFX/generated/images/src/Pump/image_FAN_SB_04.d \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_02.d \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_03.d \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_04.d \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_05.d \
./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_main.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/Pump/%.o TouchGFX/generated/images/src/Pump/%.su: ../TouchGFX/generated/images/src/Pump/%.cpp TouchGFX/generated/images/src/Pump/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../USB_HOST/App -I../USB_HOST/Target -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-Pump

clean-TouchGFX-2f-generated-2f-images-2f-src-2f-Pump:
	-$(RM) ./TouchGFX/generated/images/src/Pump/image_FAN_SB_01.d ./TouchGFX/generated/images/src/Pump/image_FAN_SB_01.o ./TouchGFX/generated/images/src/Pump/image_FAN_SB_01.su ./TouchGFX/generated/images/src/Pump/image_FAN_SB_02.d ./TouchGFX/generated/images/src/Pump/image_FAN_SB_02.o ./TouchGFX/generated/images/src/Pump/image_FAN_SB_02.su ./TouchGFX/generated/images/src/Pump/image_FAN_SB_03.d ./TouchGFX/generated/images/src/Pump/image_FAN_SB_03.o ./TouchGFX/generated/images/src/Pump/image_FAN_SB_03.su ./TouchGFX/generated/images/src/Pump/image_FAN_SB_04.d ./TouchGFX/generated/images/src/Pump/image_FAN_SB_04.o ./TouchGFX/generated/images/src/Pump/image_FAN_SB_04.su ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_02.d ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_02.o ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_02.su ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_03.d ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_03.o ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_03.su ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_04.d ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_04.o ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_04.su ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_05.d ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_05.o ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_05.su ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_main.d ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_main.o ./TouchGFX/generated/images/src/Pump/image_PUMP_OS2_main.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-Pump

