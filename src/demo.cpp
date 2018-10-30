#include <avr/controller.hpp>

int main()
  {
  if(avr::mcu::pinc::get<avr::pin::three>())
    {
    return avr::mcu::pinc::get_unsafe(avr::pin::four);
    }
  return avr::mcu::pinc::get_bit<6>();
  }
