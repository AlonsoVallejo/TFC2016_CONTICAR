################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/mcl/ADC.c" \
"../Sources/mcl/ARM_SysTick.c" \
"../Sources/mcl/CrystalClock.c" \
"../Sources/mcl/GPIO.c" \
"../Sources/mcl/TPM.c" \
"../Sources/mcl/interrupts.c" \
"../Sources/mcl/uart.c" \

C_SRCS += \
../Sources/mcl/ADC.c \
../Sources/mcl/ARM_SysTick.c \
../Sources/mcl/CrystalClock.c \
../Sources/mcl/GPIO.c \
../Sources/mcl/TPM.c \
../Sources/mcl/interrupts.c \
../Sources/mcl/uart.c \

OBJS += \
./Sources/mcl/ADC.o \
./Sources/mcl/ARM_SysTick.o \
./Sources/mcl/CrystalClock.o \
./Sources/mcl/GPIO.o \
./Sources/mcl/TPM.o \
./Sources/mcl/interrupts.o \
./Sources/mcl/uart.o \

C_DEPS += \
./Sources/mcl/ADC.d \
./Sources/mcl/ARM_SysTick.d \
./Sources/mcl/CrystalClock.d \
./Sources/mcl/GPIO.d \
./Sources/mcl/TPM.d \
./Sources/mcl/interrupts.d \
./Sources/mcl/uart.d \

OBJS_QUOTED += \
"./Sources/mcl/ADC.o" \
"./Sources/mcl/ARM_SysTick.o" \
"./Sources/mcl/CrystalClock.o" \
"./Sources/mcl/GPIO.o" \
"./Sources/mcl/TPM.o" \
"./Sources/mcl/interrupts.o" \
"./Sources/mcl/uart.o" \

C_DEPS_QUOTED += \
"./Sources/mcl/ADC.d" \
"./Sources/mcl/ARM_SysTick.d" \
"./Sources/mcl/CrystalClock.d" \
"./Sources/mcl/GPIO.d" \
"./Sources/mcl/TPM.d" \
"./Sources/mcl/interrupts.d" \
"./Sources/mcl/uart.d" \

OBJS_OS_FORMAT += \
./Sources/mcl/ADC.o \
./Sources/mcl/ARM_SysTick.o \
./Sources/mcl/CrystalClock.o \
./Sources/mcl/GPIO.o \
./Sources/mcl/TPM.o \
./Sources/mcl/interrupts.o \
./Sources/mcl/uart.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/mcl/ADC.o: ../Sources/mcl/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcl/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcl/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcl/ARM_SysTick.o: ../Sources/mcl/ARM_SysTick.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcl/ARM_SysTick.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcl/ARM_SysTick.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcl/CrystalClock.o: ../Sources/mcl/CrystalClock.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcl/CrystalClock.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcl/CrystalClock.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcl/GPIO.o: ../Sources/mcl/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcl/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcl/GPIO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcl/TPM.o: ../Sources/mcl/TPM.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcl/TPM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcl/TPM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcl/interrupts.o: ../Sources/mcl/interrupts.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcl/interrupts.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcl/interrupts.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcl/uart.o: ../Sources/mcl/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcl/uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcl/uart.o"
	@echo 'Finished building: $<'
	@echo ' '


