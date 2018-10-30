# vim: ft=cmake ts=2 sw=2 et

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/Toolchains/AVRToolchain.cmake")
endif()

cmake_minimum_required(VERSION 3.9)
project("avrxx"
  VERSION 1.0.0
  LANGUAGES C CXX
  DESCRIPTION "A modern C++ interface to AVR microcontrollers"
  )

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION On)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "MinSizeRel")
endif()

include(CMakeParseArguments)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_firmware(cpp_demo
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/demo.cpp"
  )

add_firmware(c_demo
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/demo.c"
  )

add_firmware(cpp_demo_portc
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/demo_portc.cpp"
  )

add_firmware(c_demo_portc
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/demo_portc.c"
  )

add_firmware(cpp_demo_progmem
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/demo_progmem.cpp"
  )

add_firmware(c_demo_progmem
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/demo_progmem.c"
  )
