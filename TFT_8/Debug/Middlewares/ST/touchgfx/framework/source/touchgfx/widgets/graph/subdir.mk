################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/Graph.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.cpp 

OBJS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/Graph.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.o 

CPP_DEPS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/Graph.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/%.o Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/%.su: ../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/%.cpp Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../USB_HOST/App -I../USB_HOST/Target -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Irel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-touchgfx-2f-framework-2f-source-2f-touchgfx-2f-widgets-2f-graph

clean-Middlewares-2f-ST-2f-touchgfx-2f-framework-2f-source-2f-touchgfx-2f-widgets-2f-graph:
	-$(RM) ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.d ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.o ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.su ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/Graph.d ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/Graph.o ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/Graph.su ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.d ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.o ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.su ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.d ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.o ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.su ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.d ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.o ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.su ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.d ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.o ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.su ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.d ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.o ./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.su

.PHONY: clean-Middlewares-2f-ST-2f-touchgfx-2f-framework-2f-source-2f-touchgfx-2f-widgets-2f-graph

