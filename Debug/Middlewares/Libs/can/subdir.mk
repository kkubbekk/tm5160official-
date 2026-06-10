################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Libs/can/delta.c 

OBJS += \
./Middlewares/Libs/can/delta.o 

C_DEPS += \
./Middlewares/Libs/can/delta.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Libs/can/%.o Middlewares/Libs/can/%.su Middlewares/Libs/can/%.cyclo: ../Middlewares/Libs/can/%.c Middlewares/Libs/can/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/jakub/testyjutro/Middlewares/Libs" -I"/home/jakub/testyjutro/Middlewares/Libs/can" -I"/home/jakub/testyjutro/Middlewares/Libs/tmc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Libs-2f-can

clean-Middlewares-2f-Libs-2f-can:
	-$(RM) ./Middlewares/Libs/can/delta.cyclo ./Middlewares/Libs/can/delta.d ./Middlewares/Libs/can/delta.o ./Middlewares/Libs/can/delta.su

.PHONY: clean-Middlewares-2f-Libs-2f-can

