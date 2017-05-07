################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/util/Socket.cpp 

OBJS += \
./lib/util/Socket.o 

CPP_DEPS += \
./lib/util/Socket.d 


# Each subdirectory must supply rules for building sources it contributes
lib/util/%.o: ../lib/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


