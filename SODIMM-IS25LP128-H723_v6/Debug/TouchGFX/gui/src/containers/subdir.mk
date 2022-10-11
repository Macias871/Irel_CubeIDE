################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/containers/Back_menu_container.cpp \
../TouchGFX/gui/src/containers/Menu_buttons_container.cpp \
../TouchGFX/gui/src/containers/Menu_tree_title_container.cpp \
../TouchGFX/gui/src/containers/Reg_container.cpp 

OBJS += \
./TouchGFX/gui/src/containers/Back_menu_container.o \
./TouchGFX/gui/src/containers/Menu_buttons_container.o \
./TouchGFX/gui/src/containers/Menu_tree_title_container.o \
./TouchGFX/gui/src/containers/Reg_container.o 

CPP_DEPS += \
./TouchGFX/gui/src/containers/Back_menu_container.d \
./TouchGFX/gui/src/containers/Menu_buttons_container.d \
./TouchGFX/gui/src/containers/Menu_tree_title_container.d \
./TouchGFX/gui/src/containers/Reg_container.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/containers/%.o TouchGFX/gui/src/containers/%.su: ../TouchGFX/gui/src/containers/%.cpp TouchGFX/gui/src/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-containers

clean-TouchGFX-2f-gui-2f-src-2f-containers:
	-$(RM) ./TouchGFX/gui/src/containers/Back_menu_container.d ./TouchGFX/gui/src/containers/Back_menu_container.o ./TouchGFX/gui/src/containers/Back_menu_container.su ./TouchGFX/gui/src/containers/Menu_buttons_container.d ./TouchGFX/gui/src/containers/Menu_buttons_container.o ./TouchGFX/gui/src/containers/Menu_buttons_container.su ./TouchGFX/gui/src/containers/Menu_tree_title_container.d ./TouchGFX/gui/src/containers/Menu_tree_title_container.o ./TouchGFX/gui/src/containers/Menu_tree_title_container.su ./TouchGFX/gui/src/containers/Reg_container.d ./TouchGFX/gui/src/containers/Reg_container.o ./TouchGFX/gui/src/containers/Reg_container.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-containers

