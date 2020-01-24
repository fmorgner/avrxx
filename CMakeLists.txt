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

target_compile_features("avrxx" INTERFACE
  "cxx_std_17"

  "cxx_binary_literals"
  "cxx_constexpr"
  "cxx_contextual_conversions"
  "cxx_decltype"
  "cxx_deleted_functions"
  "cxx_digit_separators"
  "cxx_explicit_conversions"
  "cxx_generic_lambdas"
  "cxx_inheriting_constructors"
  "cxx_inline_namespaces"
  "cxx_lambdas"
  "cxx_lambda_init_captures"
  "cxx_noexcept"
  "cxx_nonstatic_member_init"
  "cxx_nullptr"
  "cxx_relaxed_constexpr"
  "cxx_reference_qualified_functions"
  "cxx_right_angle_brackets"
  "cxx_rvalue_references"
  "cxx_static_assert"
  "cxx_strong_enums"
  "cxx_trailing_return_types"
  "cxx_uniform_initialization"
  "cxx_user_literals"
  "cxx_variable_templates"
  "cxx_variadic_templates"
  "cxx_template_template_parameters"
)

# === Example Firmwares === #

include("AddFirmware")

set(OLD_CMAKE_CXX_EXTENSIONS ${CMAKE_CXX_EXTENSIONS})
set(CMAKE_CXX_EXTENSIONS OFF)

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

target_compile_options("progmem" PRIVATE
  "-Wall"
  "-Wextra"
  "-Werror"
  "-pedantic-errors"
)

set(CMAKE_CXX_EXTENSIONS ${OLD_CMAKE_CXX_EXTENSIONS})