function(add_firmware TARGET)
  set(OPTIONS "HEX")
  set(SINGLE_VALUE_ARGUMENTS "MCU" "CLOCK")
  set(MULTI_VALUE_ARGUMENTS)
  
  cmake_parse_arguments(ADD_FIRMWARE
    "${OPTIONS}"
    "${SINGLE_VALUE_ARGUMENTS}"
    "${MULTI_VALUE_ARGUMENTS}"
    ${ARGN}
    )

  if(NOT ADD_FIRMWARE_MCU)
    message(FATAL_ERROR "Missing argument MCU <avr_mcu_type> in call to add_firmware")
  endif()

  if(NOT ADD_FIRMWARE_CLOCK)
    message(FATAL_ERROR "Missing argument CLOCK <clock_frequency_in_hertz> in call to add_firmware")
  endif()

  add_executable("${TARGET}"
    ${ADD_FIRMWARE_UNPARSED_ARGUMENTS}
  )

  target_link_libraries("${TARGET}" "avrxx")

  if(ADD_FIRMWARE_HEX)
    add_custom_command(TARGET "${TARGET}"
      POST_BUILD
      COMMAND "${CMAKE_OBJCOPY}"
        "-j"
        ".text"
        "-j"
        ".data"
        "-O"
        "ihex"
        "$<TARGET_FILE:${TARGET}>"
        "$<TARGET_FILE:${TARGET}>.hex"
    )
  endif()

  target_compile_options("avrxx" INTERFACE "-mmcu=${ADD_FIRMWARE_MCU}")
  target_compile_definitions("avrxx" INTERFACE "-DF_CPU=${ADD_FIRMWARE_CLOCK}")
endfunction()
