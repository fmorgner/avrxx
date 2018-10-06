# vim: ft=cmake ts=2 sw=2 et

cmake_minimum_required(VERSION 3.9)
project("avrxx"
  VERSION 1.0.0
  LANGUAGES C CXX
  DESCRIPTION "A modern C++ interface to AVR microcontrollers"
  )

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(CMakeParseArguments)

function(add_firmware TARGET)
  set(OPTIONS HEX)
  set(SINGLE_VALUE_ARGUMENTS MCU CLOCK_FREQUENCY)
  set(MULTI_VALUE_ARGUMENTS SOURCES)
  cmake_parse_arguments(ADD_FIRMWARE
    "${OPTIONS}"
    "${SINGLE_VALUE_ARGUMENTS}"
    "${MULTI_VALUE_ARGUMENTS}"
    ${ARGN}
    )

  add_executable(${TARGET} ${ADD_FIRMWARE_SOURCES})
  set_target_properties(${TARGET} PROPERTIES
    COMPILE_FLAGS "-mmcu=${ADD_FIRMWARE_MCU}"
    LINK_FLAGS "-mmcu=${ADD_FIRMWARE_MCU}"
    COMPILE_DEFINITIONS "F_CPU=${ADD_FIRMWARE_CLOCK_FREQUENCY}"
    )
  get_target_property(${TARGET}_HEX ${TARGET} RUNTIME_OUTPUT_DIRECTORY)
  add_custom_command(TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -j .text -j .data -O ihex $<TARGET_FILE:${TARGET}> $<TARGET_FILE:${TARGET}>.hex
    )
  add_custom_target(${TARGET}_disassemble
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:${TARGET}>
    )
endfunction()

include_directories("${PROJECT_SOURCE_DIR}/include")

add_firmware(demo
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/main.cpp"
  )
