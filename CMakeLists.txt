cmake_minimum_required(VERSION 3.9)

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/Toolchains/AVRToolchain.cmake")
endif()

project("avrxx"
  VERSION "1.0.0"
  LANGUAGES CXX
  DESCRIPTION "A modern C++ interface to AVR microcontrollers"
  )

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# === C++ Base Configuration === #

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# === Core Library === #

add_library("avrxx" INTERFACE)

target_include_directories("avrxx" INTERFACE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)

target_include_directories("avrxx" SYSTEM INTERFACE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/stl>"
  "$<INSTALL_INTERFACE:include/stl>"
)

# === Example Firmwares === #

include("AddFirmware")

add_firmware("basic_ports" HEX
  CLOCK "16000000"
  MCU "atmega328p"

  "src/examples/basic_ports.cpp"
)

target_compile_options("basic_ports" PRIVATE
  "-Wall"
  "-Wextra"
  "-Werror"
  "-pedantic-errors"
)

add_firmware("progmem" HEX
  CLOCK "16000000"
  MCU "atmega328p"

  "src/examples/progmem.cpp"
)

target_compile_options("basic_ports" PRIVATE
  "-Wall"
  "-Wextra"
  "-Werror"
  "-pedantic-errors"
)
