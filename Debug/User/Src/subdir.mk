################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Src/lt_can2.c \
../User/Src/lt_led.c \
../User/Src/lt_systick.c \
../User/Src/lt_timer.c \
../User/Src/lt_uart.c \
../User/Src/tmp_src.c 

OBJS += \
./User/Src/lt_can2.o \
./User/Src/lt_led.o \
./User/Src/lt_systick.o \
./User/Src/lt_timer.o \
./User/Src/lt_uart.o \
./User/Src/tmp_src.o 

C_DEPS += \
./User/Src/lt_can2.d \
./User/Src/lt_led.d \
./User/Src/lt_systick.d \
./User/Src/lt_timer.d \
./User/Src/lt_uart.d \
./User/Src/tmp_src.d 


# Each subdirectory must supply rules for building sources it contributes
User/Src/%.o User/Src/%.su User/Src/%.cyclo: ../User/Src/%.c User/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"D:/vk_project/vk_prj/vk/foundation_2/ElectronStudio_NextStone/tech_edu/INU_NCS_EDU-2024/vehicle_communication_system/fw/p2024_stm32f103c8t6/User/Inc" -I"D:/vk_project/vk_prj/vk/foundation_2/ElectronStudio_NextStone/tech_edu/INU_NCS_EDU-2024/vehicle_communication_system/fw/p2024_stm32f103c8t6/User/Src" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Src

clean-User-2f-Src:
	-$(RM) ./User/Src/lt_can2.cyclo ./User/Src/lt_can2.d ./User/Src/lt_can2.o ./User/Src/lt_can2.su ./User/Src/lt_led.cyclo ./User/Src/lt_led.d ./User/Src/lt_led.o ./User/Src/lt_led.su ./User/Src/lt_systick.cyclo ./User/Src/lt_systick.d ./User/Src/lt_systick.o ./User/Src/lt_systick.su ./User/Src/lt_timer.cyclo ./User/Src/lt_timer.d ./User/Src/lt_timer.o ./User/Src/lt_timer.su ./User/Src/lt_uart.cyclo ./User/Src/lt_uart.d ./User/Src/lt_uart.o ./User/Src/lt_uart.su ./User/Src/tmp_src.cyclo ./User/Src/tmp_src.d ./User/Src/tmp_src.o ./User/Src/tmp_src.su

.PHONY: clean-User-2f-Src

