################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../docs/respaldo de codigo/LineScanCamera.c" \

C_SRCS += \
../docs/respaldo\ de\ codigo/LineScanCamera.c \

OBJS += \
./docs/respaldo\ de\ codigo/LineScanCamera.o \

C_DEPS += \
./docs/respaldo\ de\ codigo/LineScanCamera.d \

OBJS_QUOTED += \
"./docs/respaldo de codigo/LineScanCamera.o" \

C_DEPS_QUOTED += \
"./docs/respaldo de codigo/LineScanCamera.d" \

OBJS_OS_FORMAT += \
./docs/respaldo\ de\ codigo/LineScanCamera.o \


# Each subdirectory must supply rules for building sources it contributes
docs/respaldo\ de\ codigo/LineScanCamera.o: ../docs/respaldo\ de\ codigo/LineScanCamera.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"docs/respaldo de codigo/LineScanCamera.args" -MMD -MP -MF"docs/respaldo de codigo/LineScanCamera.d" -o"docs/respaldo de codigo/LineScanCamera.o"
	@echo 'Finished building: $<'
	@echo ' '


