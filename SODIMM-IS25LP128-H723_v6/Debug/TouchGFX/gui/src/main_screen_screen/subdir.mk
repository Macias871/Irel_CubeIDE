################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/main_screen_screen/Main_screenPresenter.cpp \
../TouchGFX/gui/src/main_screen_screen/Main_screenView.cpp 

OBJS += \
./TouchGFX/gui/src/main_screen_screen/Main_screenPresenter.o \
./TouchGFX/gui/src/main_screen_screen/Main_screenView.o 

CPP_DEPS += \
./TouchGFX/gui/src/main_screen_screen/Main_screenPresenter.d \
./TouchGFX/gui/src/main_screen_screen/Main_screenView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/main_screen_screen/%.o TouchGFX/gui/src/main_screen_screen/%.su: ../TouchGFX/gui/src/main_screen_screen/%.cpp TouchGFX/gui/src/main_screen_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-main_screen_screen

clean-TouchGFX-2f-gui-2f-src-2f-main_screen_screen:
	-$(RM) ./TouchGFX/gui/src/main_screen_screen/Main_screenPresenter.d ./TouchGFX/gui/src/main_screen_screen/Main_screenPresenter.o ./TouchGFX/gui/src/main_screen_screen/Main_screenPresenter.su ./TouchGFX/gui/src/main_screen_screen/Main_screenView.d ./TouchGFX/gui/src/main_screen_screen/Main_screenView.o ./TouchGFX/gui/src/main_screen_screen/Main_screenView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-main_screen_screen
