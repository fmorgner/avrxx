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
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION On)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "MinSizeRel")
endif()

include(CMakeParseArguments)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_firmware(demo
  MCU "atmega328p"
  CLOCK_FREQUENCY "16000000"
  SOURCES
  "src/main.cpp"
  )
