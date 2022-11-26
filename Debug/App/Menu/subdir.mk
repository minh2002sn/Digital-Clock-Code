################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Menu/Main_Menu.c \
../App/Menu/Menu.c \
../App/Menu/Setting_Menu.c \
../App/Menu/Setting_Realtime_Menu.c \
../App/Menu/Setting_Timeline_Menu.c \
../App/Menu/Timeline_List_Menu.c 

OBJS += \
./App/Menu/Main_Menu.o \
./App/Menu/Menu.o \
./App/Menu/Setting_Menu.o \
./App/Menu/Setting_Realtime_Menu.o \
./App/Menu/Setting_Timeline_Menu.o \
./App/Menu/Timeline_List_Menu.o 

C_DEPS += \
./App/Menu/Main_Menu.d \
./App/Menu/Menu.d \
./App/Menu/Setting_Menu.d \
./App/Menu/Setting_Realtime_Menu.d \
./App/Menu/Setting_Timeline_Menu.d \
./App/Menu/Timeline_List_Menu.d 


# Each subdirectory must supply rules for building sources it contributes
App/Menu/%.o App/Menu/%.su: ../App/Menu/%.c App/Menu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/Libraries" -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/App" -I"D:/A_Minh/A_3rd-year university/A_Design Embedded System/BTL/Code/STM_Code/Digital_Clock_1.0/App/Menu" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Menu

clean-App-2f-Menu:
	-$(RM) ./App/Menu/Main_Menu.d ./App/Menu/Main_Menu.o ./App/Menu/Main_Menu.su ./App/Menu/Menu.d ./App/Menu/Menu.o ./App/Menu/Menu.su ./App/Menu/Setting_Menu.d ./App/Menu/Setting_Menu.o ./App/Menu/Setting_Menu.su ./App/Menu/Setting_Realtime_Menu.d ./App/Menu/Setting_Realtime_Menu.o ./App/Menu/Setting_Realtime_Menu.su ./App/Menu/Setting_Timeline_Menu.d ./App/Menu/Setting_Timeline_Menu.o ./App/Menu/Setting_Timeline_Menu.su ./App/Menu/Timeline_List_Menu.d ./App/Menu/Timeline_List_Menu.o ./App/Menu/Timeline_List_Menu.su

.PHONY: clean-App-2f-Menu

