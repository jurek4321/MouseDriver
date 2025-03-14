################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MouseControl.cpp \
../src/config.cpp 

CPP_DEPS += \
./src/MouseControl.d \
./src/config.d 

OBJS += \
./src/MouseControl.o \
./src/config.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/gtk-3.0 -I/usr/include/cairo -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/glib-2.0 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/MouseControl.d ./src/MouseControl.o ./src/config.d ./src/config.o

.PHONY: clean-src

