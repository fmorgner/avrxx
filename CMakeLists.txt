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

add_library("${PROJECT_NAME}" INTERFACE)

target_include_directories("${PROJECT_NAME}" INTERFACE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)

target_include_directories("${PROJECT_NAME}" SYSTEM INTERFACE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/avrstl>"
  "$<INSTALL_INTERFACE:include/avrstl>"
)

target_compile_features("${PROJECT_NAME}" INTERFACE
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

set_target_properties("basic_ports" PROPERTIES
  INTERPROCEDURAL_OPTIMIZATION ON
  CXX_EXTENSIONS OFF
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

set_target_properties("progmem" PROPERTIES
  INTERPROCEDURAL_OPTIMIZATION ON
  CXX_EXTENSIONS OFF
)

# === Install Configuration === #

include("CMakePackageConfigHelpers")

write_basic_package_version_file(                                                                                                   
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY "AnyNewerVersion"
)

install(TARGETS "${PROJECT_NAME}"
  EXPORT "${PROJECT_NAME}Targets"
  PUBLIC_HEADER DESTINATION "include"
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
  DESTINATION "include"
)

configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  "${PROJECT_SOURCE_DIR}/cmake/Modules/AddFirmware.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(EXPORT "${PROJECT_NAME}Targets"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)