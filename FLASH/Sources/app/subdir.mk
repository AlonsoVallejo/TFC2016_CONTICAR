################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app/LineScanCamera.c" \
"../Sources/app/ServoMotor.c" \

C_SRCS += \
../Sources/app/LineScanCamera.c \
../Sources/app/ServoMotor.c \

OBJS += \
./Sources/app/LineScanCamera.o \
./Sources/app/ServoMotor.o \

C_DEPS += \
./Sources/app/LineScanCamera.d \
./Sources/app/ServoMotor.d \

OBJS_QUOTED += \
"./Sources/app/LineScanCamera.o" \
"./Sources/app/ServoMotor.o" \

C_DEPS_QUOTED += \
"./Sources/app/LineScanCamera.d" \
"./Sources/app/ServoMotor.d" \

OBJS_OS_FORMAT += \
./Sources/app/LineScanCamera.o \
./Sources/app/ServoMotor.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/app/LineScanCamera.o: ../Sources/app/LineScanCamera.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LineScanCamera.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LineScanCamera.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/ServoMotor.o: ../Sources/app/ServoMotor.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/ServoMotor.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/ServoMotor.o"
	@echo 'Finished building: $<'
	@echo ' '


