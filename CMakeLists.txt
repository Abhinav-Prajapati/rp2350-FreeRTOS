cmake_minimum_required(VERSION 3.12)

set(NAME rp2350-rtos)
set(PICO_BOARD pico2)
set(PICO_PLATFORM rp2350)

include("$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")

project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

pico_sdk_init()

SET(FREERTOS_KERNEL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel" CACHE STRING "Common Lib")
SET(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/port/FreeRTOS-Kernel" CACHE STRING "Local Config")
include(${CMAKE_CURRENT_LIST_DIR}/port/FreeRTOS-Kernel/freertos_config.cmake)
include(FreeRTOS_Kernel_import.cmake)

add_subdirectory(src)

add_custom_target(upload
    COMMAND picotool load -x ${CMAKE_BINARY_DIR}/src/${NAME}.uf2 -f
    DEPENDS ${NAME}
    COMMENT "Uploading firmware with picotool"
)