################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app/DCMotors.c" \
"../Sources/app/LineScanCamera.c" \
"../Sources/app/PushButtons.c" \
"../Sources/app/ServoMotor.c" \

C_SRCS += \
../Sources/app/DCMotors.c \
../Sources/app/LineScanCamera.c \
../Sources/app/PushButtons.c \
../Sources/app/ServoMotor.c \

OBJS += \
./Sources/app/DCMotors.o \
./Sources/app/LineScanCamera.o \
./Sources/app/PushButtons.o \
./Sources/app/ServoMotor.o \

C_DEPS += \
./Sources/app/DCMotors.d \
./Sources/app/LineScanCamera.d \
./Sources/app/PushButtons.d \
./Sources/app/ServoMotor.d \

OBJS_QUOTED += \
"./Sources/app/DCMotors.o" \
"./Sources/app/LineScanCamera.o" \
"./Sources/app/PushButtons.o" \
"./Sources/app/ServoMotor.o" \

C_DEPS_QUOTED += \
"./Sources/app/DCMotors.d" \
"./Sources/app/LineScanCamera.d" \
"./Sources/app/PushButtons.d" \
"./Sources/app/ServoMotor.d" \

OBJS_OS_FORMAT += \
./Sources/app/DCMotors.o \
./Sources/app/LineScanCamera.o \
./Sources/app/PushButtons.o \
./Sources/app/ServoMotor.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/app/DCMotors.o: ../Sources/app/DCMotors.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/DCMotors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/DCMotors.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LineScanCamera.o: ../Sources/app/LineScanCamera.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LineScanCamera.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LineScanCamera.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/PushButtons.o: ../Sources/app/PushButtons.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/PushButtons.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/PushButtons.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/ServoMotor.o: ../Sources/app/ServoMotor.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/ServoMotor.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/ServoMotor.o"
	@echo 'Finished building: $<'
	@echo ' '


