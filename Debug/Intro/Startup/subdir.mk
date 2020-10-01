################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Intro/Startup/startup_stm32f446retx.s 

OBJS += \
./Intro/Startup/startup_stm32f446retx.o 

S_DEPS += \
./Intro/Startup/startup_stm32f446retx.d 


# Each subdirectory must supply rules for building sources it contributes
Intro/Startup/startup_stm32f446retx.o: ../Intro/Startup/startup_stm32f446retx.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Intro/Startup/startup_stm32f446retx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

