################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../myCode/CSaugroboter.cpp \
../myCode/main.cpp 

OBJS += \
./myCode/CSaugroboter.o \
./myCode/main.o 

CPP_DEPS += \
./myCode/CSaugroboter.d \
./myCode/main.d 


# Each subdirectory must supply rules for building sources it contributes
myCode/%.o: ../myCode/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


