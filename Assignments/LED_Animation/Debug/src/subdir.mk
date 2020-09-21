################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/GPIO_program.c \
../src/LedAnim_program.c \
../src/Led_program.c \
../src/RCC_program.c \
../src/SYSTICK_program.c \
../src/Simple_OS.c \
../src/main.c 

OBJS += \
./src/GPIO_program.o \
./src/LedAnim_program.o \
./src/Led_program.o \
./src/RCC_program.o \
./src/SYSTICK_program.o \
./src/Simple_OS.o \
./src/main.o 

C_DEPS += \
./src/GPIO_program.d \
./src/LedAnim_program.d \
./src/Led_program.d \
./src/RCC_program.d \
./src/SYSTICK_program.d \
./src/Simple_OS.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


