################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/domain/Boundary.cpp \
../lib/domain/Room.cpp \
../lib/domain/Wall.cpp \
../lib/domain/World.cpp 

OBJS += \
./lib/domain/Boundary.o \
./lib/domain/Room.o \
./lib/domain/Wall.o \
./lib/domain/World.o 

CPP_DEPS += \
./lib/domain/Boundary.d \
./lib/domain/Room.d \
./lib/domain/Wall.d \
./lib/domain/World.d 


# Each subdirectory must supply rules for building sources it contributes
lib/domain/%.o: ../lib/domain/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


