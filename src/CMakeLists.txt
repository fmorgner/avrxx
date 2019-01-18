# vim: ft=cmake ts=2 sw=2 et

add_firmware(cpp_demo
  SOURCES
  "demo.cpp"
)

add_firmware(c_demo
  SOURCES
  "demo.c"
)

add_firmware(cpp_demo_progmem
  SOURCES
  "demo_progmem.cpp"
)

add_firmware(c_demo_progmem
  SOURCES
  "demo_progmem.c"
)

add_firmware(cpp_demo_portc
  SOURCES
  "demo_portc.cpp"
)

add_firmware(c_demo_portc
  SOURCES
  "demo_portc.c"
)