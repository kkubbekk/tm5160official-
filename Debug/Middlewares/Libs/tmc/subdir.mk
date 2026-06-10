################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Libs/tmc/TMC5160.c \
../Middlewares/Libs/tmc/TMC_api.c \
../Middlewares/Libs/tmc/TMC_port.c 

OBJS += \
./Middlewares/Libs/tmc/TMC5160.o \
./Middlewares/Libs/tmc/TMC_api.o \
./Middlewares/Libs/tmc/TMC_port.o 

C_DEPS += \
./Middlewares/Libs/tmc/TMC5160.d \
./Middlewares/Libs/tmc/TMC_api.d \
./Middlewares/Libs/tmc/TMC_port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Libs/tmc/%.o Middlewares/Libs/tmc/%.su Middlewares/Libs/tmc/%.cyclo: ../Middlewares/Libs/tmc/%.c Middlewares/Libs/tmc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/jakub/testyjutro/Middlewares/Libs" -I"/home/jakub/testyjutro/Middlewares/Libs/can" -I"/home/jakub/testyjutro/Middlewares/Libs/tmc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Libs-2f-tmc

clean-Middlewares-2f-Libs-2f-tmc:
	-$(RM) ./Middlewares/Libs/tmc/TMC5160.cyclo ./Middlewares/Libs/tmc/TMC5160.d ./Middlewares/Libs/tmc/TMC5160.o ./Middlewares/Libs/tmc/TMC5160.su ./Middlewares/Libs/tmc/TMC_api.cyclo ./Middlewares/Libs/tmc/TMC_api.d ./Middlewares/Libs/tmc/TMC_api.o ./Middlewares/Libs/tmc/TMC_api.su ./Middlewares/Libs/tmc/TMC_port.cyclo ./Middlewares/Libs/tmc/TMC_port.d ./Middlewares/Libs/tmc/TMC_port.o ./Middlewares/Libs/tmc/TMC_port.su

.PHONY: clean-Middlewares-2f-Libs-2f-tmc

