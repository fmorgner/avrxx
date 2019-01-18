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

set(CMAKE_C_STANDARD "11")
set(CMAKE_C_EXTENSIONS Off)
set(CMAKE_C_STANDARD_REQUIRED On)

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION On)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "MinSizeRel")
endif()

add_library("avrxx" INTERFACE)
target_include_directories("avrxx" INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_compile_options("avrxx" INTERFACE "-mmcu=${AVRXX_MCU}")
target_compile_definitions("avrxx" INTERFACE "-DF_CPU=${AVRXX_CLOCK}")

add_subdirectory("src")