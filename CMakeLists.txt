# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
 set(PICO_SDK_PATH "/home/edna/experiment/dual_core/pico-sdk")
# set(LOCAL_SDK_FOLDER_NAME pico-sdk)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(complete_features C CXX ASM)

# Initialise the Raspberry Pi Pico SDK

pico_sdk_init()

add_executable(${PROJECT_NAME} pico_subsystems.c)

pico_set_program_name(complete_features "pico subsystems")
pico_set_program_version(complete_features "0.1")

pico_enable_stdio_uart(complete_features 1)
pico_enable_stdio_usb(complete_features 1)
target_link_libraries(complete_features pico_stdlib)


# Add any user requested libraries
target_link_libraries(complete_features
        hardware_spi
        hardware_i2c
        hardware_watchdog
        hardware_clocks
        hardware_timer
        )

pico_add_extra_outputs(complete_features)
if (TARGET tinyusb_device)
message(MESSAGE "building file because TinyUSB submodule is initialized in the SDK")
endif()

