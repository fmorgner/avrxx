# vim: ft=cmake ts=2 sw=2 et

if(NOT AVR_GCC)
  set(CROSS_GCC_PREFIX "avr-")
  find_program(CMAKE_CXX_COMPILER "${CROSS_GCC_PREFIX}g++" DOC "Path to ${CROSS_GCC_PREFIX}g++")
  find_program(CMAKE_C_COMPILER "${CROSS_GCC_PREFIX}gcc" DOC "Path to ${CROSS_GCC_PREFIX}g++")
  find_program(CMAKE_OBJDUMP "${CROSS_GCC_PREFIX}objdump" DOC "Path to ${CROSS_GCC_PREFIX}objdump")
  find_program(CMAKE_OBJCOPY "${CROSS_GCC_PREFIX}objcopy" DOC "Path to ${CROSS_GCC_PREFIX}objcopy")
  find_program(CMAKE_NM "${CROSS_GCC_PREFIX}nm" DOC "Path to ${CROSS_GCC_PREFIX}nm")
  find_program(CMAKE_CXX_COMPILER_RANLIB "${CROSS_GCC_PREFIX}ranlib" DOC "Path to ${CROSS_GCC_PREFIX}ranlib")
  find_program(CMAKE_STRIP "${CROSS_GCC_PREFIX}strip" DOC "Path to ${CROSS_GCC_PREFIX}strip")
  find_program(CMAKE_LINKER "${CROSS_GCC_PREFIX}ld" DOC "Path to ${CROSS_GCC_PREFIX}ld")
  find_program(CMAKE_CXX_COMPILER_AR "${CROSS_GCC_PREFIX}ar" DOC "Path to ${CROSS_GCC_PREFIX}ar")
  find_program(CMAKE_AVRDUDE "avrdude" DOC "Path to avrdude")
  mark_as_advanced(CMAKE_AVRDUDE)
  set(CMAKE_SYSTEM_NAME "Generic")
  set(CMAKE_SYSTEM_PROCESSOR "avr")
endif()

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
