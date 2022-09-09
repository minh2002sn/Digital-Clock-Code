################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Alarm.c \
../App/Rotary_Encoder.c \
../App/Timeline_Manage.c \
../App/real_time.c 

OBJS += \
./App/Alarm.o \
./App/Rotary_Encoder.o \
./App/Timeline_Manage.o \
./App/real_time.o 

C_DEPS += \
./App/Alarm.d \
./App/Rotary_Encoder.d \
./App/Timeline_Manage.d \
./App/real_time.d 


# Each subdirectory must supply rules for building sources it contributes
App/%.o App/%.su: ../App/%.c App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/Libraries" -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/App" -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/App/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App

clean-App:
	-$(RM) ./App/Alarm.d ./App/Alarm.o ./App/Alarm.su ./App/Rotary_Encoder.d ./App/Rotary_Encoder.o ./App/Rotary_Encoder.su ./App/Timeline_Manage.d ./App/Timeline_Manage.o ./App/Timeline_Manage.su ./App/real_time.d ./App/real_time.o ./App/real_time.su

.PHONY: clean-App

