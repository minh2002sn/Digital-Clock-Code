################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/DHT.c \
../Libraries/DS3231.c \
../Libraries/Delay_us.c \
../Libraries/Encoder.c \
../Libraries/LCD_I2C.c \
../Libraries/button.c \
../Libraries/flash.c 

OBJS += \
./Libraries/DHT.o \
./Libraries/DS3231.o \
./Libraries/Delay_us.o \
./Libraries/Encoder.o \
./Libraries/LCD_I2C.o \
./Libraries/button.o \
./Libraries/flash.o 

C_DEPS += \
./Libraries/DHT.d \
./Libraries/DS3231.d \
./Libraries/Delay_us.d \
./Libraries/Encoder.d \
./Libraries/LCD_I2C.d \
./Libraries/button.d \
./Libraries/flash.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o Libraries/%.su: ../Libraries/%.c Libraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/Libraries" -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/App" -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/App/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/DHT.d ./Libraries/DHT.o ./Libraries/DHT.su ./Libraries/DS3231.d ./Libraries/DS3231.o ./Libraries/DS3231.su ./Libraries/Delay_us.d ./Libraries/Delay_us.o ./Libraries/Delay_us.su ./Libraries/Encoder.d ./Libraries/Encoder.o ./Libraries/Encoder.su ./Libraries/LCD_I2C.d ./Libraries/LCD_I2C.o ./Libraries/LCD_I2C.su ./Libraries/button.d ./Libraries/button.o ./Libraries/button.su ./Libraries/flash.d ./Libraries/flash.o ./Libraries/flash.su

.PHONY: clean-Libraries

